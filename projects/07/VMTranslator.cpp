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
			//std::cout << curr_command << std::endl;
		}
			
		std::string commandType() {
			std::string command = curr_command.substr(0, curr_command.find(" "));
			//TODO: IMPLEMENT OTHER COMMAND TYPES
			if 		(command == "push") 	return "C_PUSH";
			else if (command == "pop") 		return "C_POP";
			else 							return "C_ARITHMETIC";
		}
			
		std::string arg1() {
			if (commandType() == "C_ARITHMETIC") return curr_command;
			else {
				return curr_command.substr(curr_command.find(" ")+1, curr_command.rfind(" ")-(curr_command.find(" ")+1));
			}
		}
		
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
			//	todo: implement pointer
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
};

int main() {
	std::string inpFile = "MemoryAccess/StaticTest/StaticTest.vm";
	std::string outFile = "MemoryAccess/StaticTest/StaticTest.asm";
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
	}
	
	obj_cw.close();
	std::cout << "Translation completed successfully." << std::endl;
	return 0;
}
