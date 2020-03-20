#include <iostream>
#include <fstream>
#include <cctype>
#include <unordered_map>

typedef std::unordered_map<std::string, std::string> stringmap;

class Parser {
	std::string curr_command;
	std::ifstream inp;
		
	public:
		Parser(std::string inpFile) {
			inp.open(inpFile);
			if (!inp) {
				std::cout << "Cannot open input file.\n";
				inp.close();
			} 
		}
			
		bool hasMoreCommands() {
			std::getline(inp, curr_command);
			return !inp.eof();
		}
		
		void advance() {
			while (!isalpha(curr_command[0]) && !inp.eof()) {
				std::getline(inp, curr_command);
			} 
			//remove in-line comments
			curr_command = curr_command.substr(0, curr_command.find("/")-1);
			//remove trailing whitespace
		    while (curr_command[curr_command.length()-1] == ' ') { 
				curr_command.erase(curr_command.length()-1, curr_command.length()); 
			}
		}
			
		std::string commandType() {
			std::string command = curr_command.substr(0, curr_command.find(" "));
			//TODO: IMPLEMENT OTHER COMMAND TYPES
			if 		(command == "push") 	return "C_PUSH";
			else if (command == "pop") 		return "C_POP";
			else if (command == "label") 	return "C_LABEL";
			else if (command == "if-goto") 	return "C_IF";
			else if (command == "goto") 	return "C_GOTO";
			else 							return "C_ARITHMETIC";
		}
			
		//returns 1st argument in curr_command
		std::string arg1() {
			if (commandType() == "C_ARITHMETIC") return curr_command;
			else {
				return curr_command.substr(curr_command.find(" ")+1, curr_command.rfind(" ")-(curr_command.find(" ")+1));
			}
		}
		
		//returns 2nd argument in curr_command
		//call if (obj_parser.commandType() == "C_PUSH" || obj_parser.commandType() == "C_POP")
		int arg2() {
			return stoi(curr_command.substr(curr_command.rfind(" ")+1, std::string::npos));
		}
};

class CodeWriter {
	std::ofstream out;
	int label_cnt = 0;
						
	public:
		CodeWriter(std::string outFile) {
			out.open(outFile);
			if (!out) {
				std::cout << "Cannot open output file.\n";
				out.close();
			}
		}
			
		void writeArithmetic(std::string command) {
			out << "@SP" 	<< std::endl;
			out << "M=M-1" 	<< std::endl;
			out << "A=M" 	<< std::endl;
			if (command == "neg") {
				out << "M=-M"	<< std::endl;
			}
			else if (command == "not") {
				out << "M=!M"	<< std::endl;
			}
			else {
				out << "D=M" 	<< std::endl;
				out << "@SP" 	<< std::endl;
				out << "M=M-1" 	<< std::endl;
				out << "A=M" 	<< std::endl;
				if (command == "add") {
					out << "M=M+D" 	<< std::endl;
				}
				else if (command == "sub") {
					out << "M=M-D" 	<< std::endl;
				}
				else if (command == "eq" || command == "lt" || command == "gt") {
					out << "D=M-D" 	<< std::endl;
					out << "M=-1" 	<< std::endl;
					out << "@NEXT" 	<< label_cnt << std::endl;
					if (command == "eq") 		out << "D;JEQ" 	<< std::endl;
					else if (command == "lt") 	out << "D;JLT" 	<< std::endl;
					else if (command == "gt") 	out << "D;JGT" 	<< std::endl;
					out << "@SP" 	<< std::endl;
					out << "A=M" 	<< std::endl;
					out << "M=0" 	<< std::endl;
					out << "(NEXT" 	<< label_cnt << ")" << std::endl;
					++label_cnt;
				}
				else if (command == "and") {
					out << "M=D&M" 	<< std::endl;
				}
				else if (command == "or") {
					out << "M=D|M" 	<< std::endl;
				}
			}
			out << "@SP" 		<< std::endl;
			out << "M=M+1" 		<< std::endl;
		}
			
		void writePushPop(std::string command, std::string seg, int index, stringmap seg_name) {
			if (command == "C_PUSH") {
				if (seg == "pointer") {
					if (index == 0) out << "@THIS" << std::endl;
					else 			out << "@THAT" << std::endl;
					out << "D=M" << std::endl;
				}
				else {
					out << "@" << index << std::endl;
					out << "D=A" 		<< std::endl;
					if (seg != "constant") {
						out << "@" << seg_name[seg] << std::endl;
						if (seg == "temp" || seg == "static")
							out << "D=D+A"	<< std::endl;
						else
							out << "D=D+M"	<< std::endl;
						out << "A=D"	<< std::endl;
						out << "D=M"	<< std::endl;
					}
				}
				out << "@SP" 		<< std::endl;
				out << "A=M" 		<< std::endl;
				out << "M=D" 		<< std::endl;
				out << "@SP" 		<< std::endl;
				out << "M=M+1" 		<< std::endl;
			}
			else if (command == "C_POP") {
				if (seg == "pointer") {
					if (index == 0) out << "@THIS" << std::endl;
					else 			out << "@THAT" << std::endl;
					out << "D=A" << std::endl;
				}
				else {
					out << "@" << index << std::endl;
					out << "D=A" 	<< std::endl;
					out << "@" << seg_name[seg] << std::endl;
					if (seg == "temp" || seg == "static")
						out << "D=D+A"	<< std::endl;
					else
						out << "D=D+M"	<< std::endl;
				}
				out << "@13"	<< std::endl;
				out << "M=D"	<< std::endl;
				out << "@SP" 	<< std::endl;
				out << "M=M-1" 	<< std::endl;
				out << "A=M" 	<< std::endl;
				out << "D=M" 	<< std::endl;
				out << "@13"	<< std::endl;
				out << "A=M"	<< std::endl;
				out << "M=D"	<< std::endl;
			}
		}
			
		void close() {
			out << "(END)" << std::endl;
			out << "@END"  << std::endl;
			out << "0;JMP" << std::endl;
			out.close();
		}
		
		void setFileName(std::string fileName) {
			//inform codewriter that translation of new file has started
		}
		
		void writeInit() {
			//bootstrap code at beginning
		}
		
		void writeLabel(std::string s) {
			out << "(" << s << ")" << std::endl;
		}
		
		void writeGoto(std::string s) {
			out << "@" << s	<< std::endl;
			out << "0;JMP" 	<< std::endl;
		}
		
		void writeIf(std::string s) {
			out << "@SP" 	<< std::endl;
			out << "M=M-1" 	<< std::endl;
			out << "A=M" 	<< std::endl;
			out << "D=M" 	<< std::endl;
			out << "@" << s	<< std::endl;
			out << "D;JGT" 	<< std::endl;
		}
		
		void writeFunction(std::string functionName, int numVars) {
			//assmbly code
		}
		
		void writeCall(std::string functionName, int numArgs) {
			//assmbly code
		}
		
		void writeReturn() {
			//assembly code
		}
};

int main() {	
	//input and output files
	std::string inpFile = "ProgramFlow/FibonacciSeries/FibonacciSeries.vm";
	std::string outFile = "ProgramFlow/FibonacciSeries/FibonacciSeries.asm";
	
	//names of segments in HACK platform
	stringmap seg_name ({{"local",		"LCL"},
						{"argument",	"ARG"},
						{"this",		"THIS"},
						{"that",		"THAT"},
						{"static",		"16"},
						{"temp",		"5"}});
	
	Parser obj_parser(inpFile);
	CodeWriter obj_cw(outFile);
	
	while (obj_parser.hasMoreCommands()) {
		obj_parser.advance();
		if 		(obj_parser.commandType() == "C_ARITHMETIC") 									obj_cw.writeArithmetic(obj_parser.arg1());
		else if (obj_parser.commandType() == "C_PUSH" || obj_parser.commandType() == "C_POP") 	obj_cw.writePushPop(obj_parser.commandType(), obj_parser.arg1(), obj_parser.arg2(), seg_name);
		else if (obj_parser.commandType() == "C_LABEL") 										obj_cw.writeLabel(obj_parser.arg1());
		else if (obj_parser.commandType() == "C_IF") 											obj_cw.writeIf(obj_parser.arg1());
		else if (obj_parser.commandType() == "C_GOTO") 											obj_cw.writeGoto(obj_parser.arg1());
	}
	
	obj_cw.close();
	std::cout << "Translation completed successfully." << std::endl;
	return 0;
}
