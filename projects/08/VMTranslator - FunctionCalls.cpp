#include <iostream>
#include <fstream>
#include <cctype>
#include <array>
#include <string>
#include <vector>
#include <unordered_map>

typedef std::unordered_map<std::string, std::string> stringmap;

class Parser {
	std::string curr_command;
	std::ifstream inp;
		
	public:
		Parser(std::string inpFile) {
			inp.open(inpFile);
			if (!inp) {
				std::cout << "Cannot open input file " << inpFile << ".\n";
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
			else if (command == "function") return "C_FUNCTION";
			else if (command == "return") 	return "C_RETURN";
			else if (command == "call") 	return "C_CALL";
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
		
		void close() {
			std::cout << "Closing input file.\n";
			inp.close();
		}
};

class CodeWriter {
	std::ofstream out;
	std::string fileName;
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
					out << "D=M"		<< std::endl;
				}
				else if (seg == "static") {
					out << "@" << fileName << "." << index << std::endl;
					out << "D=M"		<< std::endl;
				}
				else {
					out << "@" << index << std::endl;
					out << "D=A" 		<< std::endl;
					if (seg != "constant") {
						out << "@" << seg_name[seg] << std::endl;
						if (seg == "temp")
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
				else if (seg == "static") {
					out << "@" << fileName << "." << index << std::endl;
					out << "D=A" << std::endl;
				}
				else {
					out << "@" << index << std::endl;
					out << "D=A" 	<< std::endl;
					out << "@" << seg_name[seg] << std::endl;
					if (seg == "temp")
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
		
		void setFileName(std::string s) {
			fileName = s;
		}
		
		void writeInit() {
			out << "@261" 	<< std::endl;
			out << "D=A" 	<< std::endl;
			out << "@SP" 	<< std::endl;
			out << "M=D" 	<< std::endl;
			//writeCall("Sys.init", 0);
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
			out << "D;JNE" 	<< std::endl;
		}
		
		void writeFunction(std::string functionName, int numVars) {
			out << "(" << functionName << ")" << std::endl;
			if (numVars > 0) {
				//local 0 = 0
				out << "@LCL" 	<< std::endl;
				out << "A=M" 	<< std::endl;
				out << "M=0" 	<< std::endl;
			}
		}
		
		void writeCall(std::string functionName, int numArgs) {
			//push retAddrLabel
			std::string retAddrLabel = "$ret." + std::to_string(label_cnt);
			++label_cnt;
			
			out << "@" << retAddrLabel		  << std::endl;
			out << "D=A"		<< std::endl;
			out << "@SP"		<< std::endl;
			out << "A=M"		<< std::endl;
			out << "M=D"		<< std::endl;
			out << "@SP"		<< std::endl;
			out << "M=M+1"		<< std::endl;
			//push LCL
			out << "@LCL"		<< std::endl;
			out << "D=M"		<< std::endl;
			out << "@SP"		<< std::endl;
			out << "A=M"		<< std::endl;
			out << "M=D"		<< std::endl;
			out << "@SP"		<< std::endl;
			out << "M=M+1"		<< std::endl;
			//push ARG
			out << "@ARG"		<< std::endl;
			out << "D=M"		<< std::endl;
			out << "@SP"		<< std::endl;
			out << "A=M"		<< std::endl;
			out << "M=D"		<< std::endl;
			out << "@SP"		<< std::endl;
			out << "M=M+1"		<< std::endl;
			//push THIS
			out << "@THIS"		<< std::endl;
			out << "D=M"		<< std::endl;
			out << "@SP"		<< std::endl;
			out << "A=M"		<< std::endl;
			out << "M=D"		<< std::endl;
			out << "@SP"		<< std::endl;
			out << "M=M+1"		<< std::endl;
			//push THAT
			out << "@THAT"		<< std::endl;
			out << "D=M"		<< std::endl;
			out << "@SP"		<< std::endl;
			out << "A=M"		<< std::endl;
			out << "M=D"		<< std::endl;
			out << "@SP"		<< std::endl;
			out << "M=M+1"		<< std::endl;
			//ARG = SP-5-nArgs
			out << "@SP"		<< std::endl;
			out << "D=M"		<< std::endl;
			out << "@5"			<< std::endl;
			out << "D=D-A"		<< std::endl;
			out << "@" << numArgs << std::endl;
			out << "D=D-A"		<< std::endl;
			out << "@ARG"		<< std::endl;
			out << "M=D"		<< std::endl;
			//LCL = SP
			out << "@SP"		<< std::endl;
			out << "D=M"		<< std::endl;
			out << "@LCL"		<< std::endl;
			out << "M=D"		<< std::endl;
			//goto functionName
			out << "@" << functionName << std::endl;
			out << "0;JMP"	 	 << std::endl;
			//(retAddrLabel)
			out << "(" << retAddrLabel << ")" << std::endl;
		}
		
		void writeReturn() {
			//endFrame = LCL (store endFrame in RAM[13])
			out << "@LCL"	 	 << std::endl;
			out << "D=M"	 	 << std::endl;
			out << "@13"	 	 << std::endl;
			out << "M=D"	 	 << std::endl;
			//retAddr = *(endFrame - 5)  (stores retAddr in RAM[14])
			out << "@5"			 << std::endl;
			out << "D=D-A"	 	 << std::endl; //D = endFrame - 5
			out << "A=D"		 << std::endl;
			out << "D=M"		 << std::endl;
			out << "@14"	 	 << std::endl;
			out << "M=D"	 	 << std::endl;
			//*ARG=pop() (stores return value in *ARG)
			out << "@SP"	 	 << std::endl;
			out << "A=M-1"	 	 << std::endl;
			out << "D=M"	 	 << std::endl;
			out << "@ARG"	 	 << std::endl;
			out << "A=M"	 	 << std::endl;
			out << "M=D"	 	 << std::endl;
			//SP = ARG+1
			out << "@ARG"	 	 << std::endl;
			out << "D=M+1"	 	 << std::endl;
			out << "@SP"	 	 << std::endl;
			out << "M=D"	 	 << std::endl;
			//THAT=*(endFrame–1)
			out << "@13"		 << std::endl;
			out << "D=M"	 	 << std::endl;
			out << "@1"			 << std::endl;
			out << "D=D-A"	 	 << std::endl; //D = endFrame - 1
			out << "A=D"		 << std::endl;
			out << "D=M"	 	 << std::endl;
			out << "@THAT"		 << std::endl;
			out << "M=D"	 	 << std::endl;
			//THIS=*(endFrame–2)
			out << "@13"		 << std::endl;
			out << "D=M"	 	 << std::endl;
			out << "@2"			 << std::endl;
			out << "D=D-A"	 	 << std::endl; //D = endFrame - 2
			out << "A=D"		 << std::endl;
			out << "D=M"	 	 << std::endl;
			out << "@THIS"		 << std::endl;
			out << "M=D"	 	 << std::endl;
			//ARG=*(endFrame–3)
			out << "@13"		 << std::endl;
			out << "D=M"	 	 << std::endl;
			out << "@3"			 << std::endl;
			out << "D=D-A"	 	 << std::endl; //D = endFrame - 3
			out << "A=D"		 << std::endl;
			out << "D=M"	 	 << std::endl;
			out << "@ARG"		 << std::endl;
			out << "M=D"	 	 << std::endl;
			//LCL=*(endFrame–4)
			out << "@13"		 << std::endl;
			out << "D=M"	 	 << std::endl;
			out << "@4"			 << std::endl;
			out << "D=D-A"	 	 << std::endl; //D = endFrame - 4
			out << "A=D"		 << std::endl;
			out << "D=M"	 	 << std::endl;
			out << "@LCL"		 << std::endl;
			out << "M=D"	 	 << std::endl;
			//goto retAddr
			out << "@14"		 << std::endl;
			out << "A=M"		 << std::endl;
			out << "0;JMP"	 	 << std::endl;
		}
};

int main() {	
	//NOTE: VM FILE NAMES ARE HARD-CODED BECAUSE FEW C++17 COMPILERS EXIST AS OF TIME OF WRITING
	//input and output files
	std::string dirName = "StaticsTest";
	std::vector<std::string> inpFileNames(0);
	inpFileNames.push_back("Sys.vm");
	inpFileNames.push_back("Class1.vm");
	inpFileNames.push_back("Class2.vm");
	//inpFileNames.push_back("Main.vm");
	std::string inpFile;
	std::string inpDir  = "FunctionCalls/" + dirName + "/";
	std::string outFile = "FunctionCalls/" + dirName + "/" + dirName + ".asm";
	
	//names of segments in HACK platform
	stringmap seg_name ({{"local",		"LCL"},
						{"argument",	"ARG"},
						{"this",		"THIS"},
						{"that",		"THAT"},
						{"static",		"16"},
						{"temp",		"5"}});
	
	CodeWriter obj_cw(outFile);
	//write bootstrap code
	obj_cw.writeInit();
	
	for (int tmp=0; tmp < inpFileNames.size(); ++tmp) {
		std::cout << "Opening " << inpFileNames[tmp] << std::endl;
		inpFile = inpDir + inpFileNames[tmp];
			Parser obj_parser(inpFile);
			obj_cw.setFileName(inpFileNames[tmp]);
			
			//translate each line
			while (obj_parser.hasMoreCommands()) {
				obj_parser.advance();
				if 		(obj_parser.commandType() == "C_ARITHMETIC") 									obj_cw.writeArithmetic(obj_parser.arg1());
				else if (obj_parser.commandType() == "C_PUSH" || obj_parser.commandType() == "C_POP") 	obj_cw.writePushPop(obj_parser.commandType(), obj_parser.arg1(), obj_parser.arg2(), seg_name);
				else if (obj_parser.commandType() == "C_LABEL") 										obj_cw.writeLabel(obj_parser.arg1());
				else if (obj_parser.commandType() == "C_IF") 											obj_cw.writeIf(obj_parser.arg1());
				else if (obj_parser.commandType() == "C_GOTO") 											obj_cw.writeGoto(obj_parser.arg1());
				else if (obj_parser.commandType() == "C_FUNCTION") {
					obj_cw.writeFunction(obj_parser.arg1(), obj_parser.arg2());
					//push 0 numVars times
					for (int i=0; i<obj_parser.arg2(); ++i) {
						obj_cw.writePushPop("C_PUSH", "local", 0, seg_name);
					}
				} 										
				else if (obj_parser.commandType() == "C_RETURN") 										obj_cw.writeReturn();
				else if (obj_parser.commandType() == "C_CALL") 											obj_cw.writeCall(obj_parser.arg1(), obj_parser.arg2());
			}
			
			obj_parser.close();
	}

	obj_cw.close();
	std::cout << "Translation completed successfully." << std::endl;
	return 0;
}
