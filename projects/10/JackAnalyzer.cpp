#include <unordered_map>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

typedef std::vector<std::string> stringvec;


bool findInVec(std::string s, stringvec vec) {
    stringvec::iterator it;
    it = find(vec.begin(), vec.end(), s);
    return it != vec.end();
}

bool isInt(std::string s) {
    return s.find_first_not_of("0123456789") == std::string::npos;
}

std::string strVecCat(stringvec vec) {
    std::string str = "";
    for (int i=0; i<vec.size(); ++i) {str += vec[i];}
    return str;
}


class JackTokenizer {
    private:
        std::string curr_tkn;
        std::string curr_line;
        stringvec   curr_line_tkns;
        std::ifstream inp;
        std::ofstream out;

        //pre-defined in Jack grammar
        const stringvec keyWords =  {"class", "constructor", "function", "method", 
                                    "field", "static", "var", "int", "char", "boolean", 
                                    "void", "true", "false", "null", "this", "let", "do", 
                                    "if", "else", "while", "return"};
        const stringvec symbols =   {"{", "}", "(", ")", "[", "]", ".", ",", ";",
                                    "+", "-", "*", "/", "&", "|", "<", ">", "=", "~"};

        const std::unordered_map<std::string, std::string> char_map =  {{"<", "&lt;"},
                                                                        {">", "&gt;"},
                                                                        {"&", "&amp;"},
                                                                        {"\"", "&quot;"}};

        bool hasMoreTokens() {
            if (curr_line_tkns.empty()) {
                //get curr_line w/o comments
                while (curr_line.empty() && !inp.eof()) {
                    std::getline(inp >> std::ws, curr_line);
                    if (curr_line.find("//") != std::string::npos) {
                        curr_line.erase(curr_line.find("//"), std::string::npos-curr_line.find("//"));
                    }
                    if (curr_line.find("/*") != std::string::npos) {
                        curr_line.erase(curr_line.find("/*"), std::string::npos-curr_line.find("*/"));
                    }
                    if (curr_line.find("/**")   != std::string::npos ||
                        curr_line.find("*/")    != std::string::npos ||
                        curr_line[0] == '*' ) {
                        curr_line = "";
                    }
                    curr_line_tkns.clear();
                }
            }
            return (inp.eof()) ? false:true;
        }

        void advance() {
            //tokenize current line
            if (curr_line_tkns.size() == 0) {
                std::string delim_str = strVecCat(symbols) + " ";
                std::size_t end_pos;
                bool isString = false;
                
                while (!curr_line.empty()) {
                    //if current token is symbol
                    if (delim_str.find(curr_line[0]) != std::string::npos) {end_pos = 1;}
                    else {
                        //if string
                        if (curr_line[0] == '"') {
                            end_pos = curr_line.find_first_of('"', 1) + 1;
                        } else {
                            end_pos = curr_line.find_first_of(delim_str);
                        }
                    }
                    //push next token to vector
                    curr_line_tkns.push_back(curr_line.substr(0, end_pos));
                    //erase pushed token from line
                    curr_line.erase(0, end_pos);
                    //discard leading whitespace
                    curr_line.erase(0, curr_line.find_first_not_of(" \t"));
                }
            }

            curr_tkn = curr_line_tkns.front();
            curr_line_tkns.erase(curr_line_tkns.begin());
        }

        const std::string tokenType() {
            std::string tkn_type;
            (findInVec(curr_tkn, keyWords))              ? tkn_type = "keyword"         :
            (findInVec(curr_tkn, symbols))               ? tkn_type = "symbol"          :
            (isInt(curr_tkn))                            ? tkn_type = "integerConstant" :
            ('"' == curr_tkn.front() && '"' == curr_tkn.back()) ? tkn_type = "stringConstant"  : 
                                                           tkn_type = "identifier";
            return tkn_type;
        }

        std::string symbol() {
            //replace <>," with &lt; &gt; &quot; &amp;
            if (char_map.find(curr_tkn) != char_map.end()) {return char_map.at(curr_tkn);}
            else {return curr_tkn;}
        }

        std::string stringVal() {
            //remove quotation marks
            std::string str_val(curr_tkn, 1, curr_tkn.length()-2);
            return str_val;
        }

        void writeToken() {
            std::string curr_tkn_type = tokenType();
            out << "<" << curr_tkn_type << "> ";
            (curr_tkn_type == "symbol")         ? out << symbol()     << " " :
            (curr_tkn_type == "stringConstant") ? out << stringVal()  << " " :
                                                  out << curr_tkn     << " ";
            out << "</" << curr_tkn_type << "> " << std::endl;
        }

    public:
        JackTokenizer(std::string filename) {
            //open input stream w/ error handling
            inp.open(filename + ".jack");
            if (!inp) {
                std::cout << "ERROR: JackTokenizer failed to open " << filename << ".jack.\n";
                inp.close();
            } else {
                std::cout << "SUCCESS: JackTokenizer loaded " << filename << ".jack successfully.\n";
            }

            //open output stream w/ error handling
            out.open(filename + "Tokens.xml");
            if (!out) {
                std::cout << "ERROR: JackTokenizer failed to open " << filename << "Tokens.xml.\n";
                out.close();
            } else {
                std::cout << "SUCCESS: JackTokenizer loaded " << filename << "Tokens.xml successfully.\n";
            }
        }

        void writeAllTokens() {
            out << "<tokens>" << std::endl;
            while (hasMoreTokens()) {
                advance();
                writeToken();
            }
            out << "</tokens>" << std::endl;
        }

        void close() {
            inp.close();
            out.close();
            std::cout << "SUCCESS: JackTokenizer translation completed successfully.\n";
        }
};


class CompilationEngine {
    private:
        std::string curr_line;
        std::string curr_tkn; 
        // curr_tkn = curr_line.substr(curr_line.find(">") + 2, curr_line.rfind - 1)/
        std::ifstream inp;
        std::ofstream out;

        void setCurrTkn() {
            if (curr_line != "</tokens>") {
                curr_tkn = curr_line.substr(curr_line.find(">") + 2, curr_line.rfind("<") - curr_line.find(">") - 3);
            }
        }

        void printCurrLine() {
            out << curr_line << std::endl;
            do {std::getline(inp, curr_line);} while (curr_line.empty());
            setCurrTkn();
        }

        void printError() {
            std::cout << "ERROR: Encountered unknown token" << std::endl;
        }

        //compiles static & field variable declarations
        /* STRUCTURE: ('static'|'field') type varName (','varName)*';' */
        void compileClassVarDec() {
            out << "<classVarDec>" << std::endl;

            while (curr_tkn != ";") {printCurrLine();}
            
            printCurrLine(); //to print ;
            out << "</classVarDec>" << std::endl;
        }

        //compiles a complete method, function, or constructor
        /* STRUCTURE: ('constructor'|'function'|'method') ('void'|type)
                        subroutineName '('parameterList')'subRoutineBody */
        void compileSubroutineDec() {
            out << "<subroutineDec>" << std::endl;

            while (curr_tkn != "(") {printCurrLine();}
            
            printCurrLine(); //to print (
            compileParameterList();
            printCurrLine(); //to print )

            compileSubroutineBody();
            out << "</subroutineDec>" << std::endl;
        }

        //does not handle enclosing "()"
        //STRUCTURE: ((type varName) (','type varName)*)?
        void compileParameterList() {
            out << "<parameterList>" << std::endl;
            
            while (curr_tkn != ")") {printCurrLine();}

            out << "</parameterList>" << std::endl;
        }

        //STRUCTURE: '{' varDec* statements '}'
        void compileSubroutineBody() {
            out << "<subroutineBody>" << std::endl;
            printCurrLine(); //to print {
            
            while (curr_tkn == "var") {compileVarDec();}

            compileStatements();
            printCurrLine(); //to print }
            out << "</subroutineBody>" << std::endl;
        }

        //does not need to be enclosed by <subroutineCall>
        //STRUCTURE: subroutineName '('expressionList')'|(className|varName)'.'subroutineName'('expressionList')'
        void compileSubroutineCall() {
            //print subroutineName|className|varName
            printCurrLine();

            //if STRUCTURE: subroutineName '('expressionList')'
            if (curr_tkn == "(") {
                printCurrLine();
                compileExpressionList();
                printCurrLine();
            } 
            
            //if STRUCTURE: (className|varName)'.'subroutineName'('expressionList')'
            else if (curr_tkn == ".") {
                //print . subroutineName (
                for(int i=0; i<3; ++i) {printCurrLine();}
                compileExpressionList();
                printCurrLine(); //print )
            }
        }

        /* STRUCTURE: 'var' type varName (',' varName)*';' */
        void compileVarDec() {
            out << "<varDec>" << std::endl;
            
            while (curr_tkn != ";") {printCurrLine();}

            printCurrLine(); //to print ;
            out << "</varDec>" << std::endl;
        }

        //(let/if/while/do/return statement)*
        void compileStatements() {
            out << "<statements>" << std::endl;

            while (curr_tkn == "let"    || curr_tkn == "if" || curr_tkn == "while"
                || curr_tkn == "do"     || curr_tkn == "return") {
                (curr_tkn == "let")    ? compileLet() :
                (curr_tkn == "if")     ? compileIf() :
                (curr_tkn == "while")  ? compileWhile() :
                (curr_tkn == "do")     ? compileDo() : 
                (curr_tkn == "return") ? compileReturn() : printError();
            }

            out << "</statements>" << std::endl;
        }

        //STRUCTURE: 'let' varName ('['expression']')? '=' expression ';'
        void compileLet() {
            out << "<letStatement>" << std::endl;

            while (curr_tkn != "[" && curr_tkn != "=") {printCurrLine();}

            if (curr_tkn == "[") {
                printCurrLine(); //to print [
                compileExpression();
                printCurrLine(); //to print ]
            }
            
            printCurrLine(); //to print =
            compileExpression();
            printCurrLine(); //to print ;

            out << "</letStatement>" << std::endl;
        }

        //STRUCTURE: 'if''('expression')''{'statements'}'('else''{'statements'}')?
        void compileIf() {
            out << "<ifStatement>" << std::endl;

            //print if (
            for (int i=0; i<2; ++i) {printCurrLine();} 
            compileExpression();
            //print ) {
            for (int i=0; i<2; ++i) {printCurrLine();} 
            compileStatements();
            printCurrLine(); //print }

            while (curr_tkn == "else") {
                //print else (
                for (int i=0; i<2; ++i) {printCurrLine();}
                compileStatements();
                printCurrLine(); //print }
            }

            out << "</ifStatement>" << std::endl;
        }

        //STRUCTURE: 'while''('expression')''{'statements'}'
        void compileWhile() {
            out << "<whileStatement>" << std::endl;

            //print while (
            for (int i=0; i<2; ++i) {printCurrLine();} 
            compileExpression();
            //print ) {
            for (int i=0; i<2; ++i) {printCurrLine();} 
            compileStatements();
            printCurrLine(); //print }

            out << "</whileStatement>" << std::endl;
        }

        //STRUCTURE: 'do' subroutineCall ';'
        void compileDo() {
            out << "<doStatement>" << std::endl;

            printCurrLine(); //print do
            compileSubroutineCall();
            printCurrLine(); //print ;

            out << "</doStatement>" << std::endl;
        }

        //STRUCTURE: 'return' expression? ';'
        void compileReturn() {
            out << "<returnStatement>" << std::endl;

            printCurrLine(); //print return
            while (curr_tkn != ";") {compileExpression();}
            printCurrLine(); //print ;

            out << "</returnStatement>" << std::endl;
        }

        bool isTerm() {
            std::string nonterm = "=;)]},";
            bool is_t = true;

            isOp()                                                                ? is_t = false :
            curr_tkn.length()==1 && (nonterm.find(curr_tkn) != std::string::npos) ? is_t = false : true;

            return is_t;
        }

        bool isOp() {
            stringvec ops = {"+","*","/","|","-","=","&lt;","&gt;","&amp;"};
            return findInVec(curr_tkn, ops);
        }

        //STRUCTURE: term (op term)*
        void compileExpression() {
            out << "<expression>" << std::endl;

            compileTerm();
            //while curr_tkn is an operator
            while (isOp()) {
                printCurrLine();
                compileTerm();
            }

            out << "</expression>" << std::endl;
        }

        /* STRUCTURE: integerConstant|stringConstant|keywordConstant|
                      varName|varName'['expression']'|subroutineCall|
                      '('expression')'|unaryOp term */
        void compileTerm() {
            out << "<term>" << std::endl;

            //if STRUCTURE: '('expression')' 
            if (curr_tkn == "(") {
                printCurrLine(); //print (
                compileExpression();
                printCurrLine(); //print )
            } 
            //if STRUCTURE: unaryOp term
            else if (curr_tkn == "-" || curr_tkn == "~") {
                printCurrLine();
                compileTerm();
            }
            else {printCurrLine();}

            //if STRUCTURE: varName'['expression']'
            if (curr_tkn == "[") {
                printCurrLine(); //print [
                compileExpression();
                printCurrLine(); //print ]
            } 
            //if STRUCTURE: subroutineCall
            else if (curr_tkn == ".") {
                //print . subroutineName (
                for(int i=0; i<3; ++i) {printCurrLine();}
                compileExpressionList();
                printCurrLine(); //print )            
            }
            //if STRUCTURE: subroutineName '('expressionList')'
            else if (curr_tkn == "(") {
                printCurrLine();
                compileExpressionList();
                printCurrLine();
            } 

            out << "</term>" << std::endl;
        }

        //STRUCTURE: (expression(','expression)*)?
        void compileExpressionList() {
            out << "<expressionList>" << std::endl;

            if (isTerm()) {
                compileExpression();

                while (curr_tkn == ",") {
                    printCurrLine();
                    compileExpression();
                }
            }

            out << "</expressionList>" << std::endl;
        }

    public:
        CompilationEngine(std::string filename) {
            //open input stream w/ error handling
            inp.open(filename + "Tokens.xml");
            if (!inp) {
                std::cout << "ERROR: CompilationEngine failed to open " << filename << "Tokens.xml.\n";
                inp.close();
            } else {
                std::cout << "SUCCESS: CompilationEngine loaded " << filename << "Tokens.xml successfully.\n";
            }

            //open output stream w/ error handling
            out.open(filename + "Compiled.xml");
            if (!out) {
                std::cout << "ERROR: CompilationEngine failed to open " << filename << "Compiled.xml.\n";
                out.close();
            } else {
                std::cout << "SUCCESS: CompilationEngine loaded " << filename << "Compiled.xml successfully.\n";
            }
        }

        void compileClass() {
            out << "<class>" << std::endl;

            for(int i=0; i<2; ++i) std::getline(inp, curr_line); //skip <tokens>
            setCurrTkn();

            /* STRUCTURE: 'class' ClassName '{' classVarDec* subroutineDec* '}' */
            while (curr_line != "</tokens>") {
                //if classVarDec
                if (curr_tkn == "static" ||
                    curr_tkn == "field") {
                    compileClassVarDec();
                }
                //if subroutineDec
                else if (curr_tkn == "constructor" ||
                         curr_tkn == "function"||
                         curr_tkn == "method") {
                    compileSubroutineDec();
                }
                else {
                    printCurrLine();
                }
            }
            
            out << "</class>" << std::endl;
        }

        void close() {
            inp.close();
            out.close();
            std::cout << "SUCCESS: CompilationEngine translation completed successfully.\n";
        }
};

int main() {
    //"ExpressionLessSquare\Main"
    std::string inp_file;// = "ExpressionLessSquare\\Main";
    std::cin >> inp_file;

    JackTokenizer tknzr(inp_file);

    tknzr.writeAllTokens();
    tknzr.close();

    CompilationEngine cmplr(inp_file);

    cmplr.compileClass();
    cmplr.close();

    std::cout << "SUCCESS: Translation completed successfully.\n";
}