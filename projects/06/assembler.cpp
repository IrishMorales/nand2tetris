#include "parser.h"
#include "code.h"
#include "symbolTable.h"
#include <bitset>
#include <string>
#include <cctype>
#include <typeinfo>
#include <assert.h>

int main() {
	//setup in and out files
	std::string filename = "pong/Pong";
	std::string in_filename = filename + ".asm";
	std::string out_filename = filename + ".hack";
	
	Parser asmParser(in_filename);
	Code asmCode;
	SymbolTable asmTable;
	
	std::ofstream outFile;
	outFile.open(out_filename);
	
	unsigned int line_cnt = 0;
	unsigned int nxt_var_add = 16;
	
	//first pass
	while (asmParser.hasMoreCommands()) {
		asmParser.curr_command = asmParser.advance();
		
		if (asmParser.commandType() == "L_COMMAND" && !asmTable.contains(asmParser.symbol())) {
			asmTable.addEntry(asmParser.symbol(), line_cnt);
		}
		else {
			++line_cnt;
		}
	}
	
	//outFile << asmParser.hasMoreCommands() << std::endl;
	
	asmParser.returnToBegin();
	
	//outFile << asmParser.hasMoreCommands();
	
	//second pass
	while (asmParser.hasMoreCommands()) {
		
		asmParser.curr_command = asmParser.advance();
		//outFile << asmParser.curr_command << " " << asmParser.commandType() << std::endl;
		
		if (asmParser.commandType() == "A_COMMAND") {
			if (!isdigit(asmParser.symbol()[0]) && !asmTable.contains(asmParser.symbol())) {
				asmTable.addEntry(asmParser.symbol(), nxt_var_add);
				++nxt_var_add;
			}
			
			int address;
			
			if (isdigit(asmParser.symbol()[0])) {
				address = stoi(asmParser.symbol());
			}
			
			else {
				address = asmTable.getAddress(asmParser.symbol());
			}
			
			outFile << "0" + std::bitset<15>(address).to_string() << std::endl;
			
		}
		
		else if (asmParser.commandType() == "C_COMMAND") {
			outFile << "111" + asmCode.comp(asmParser.comp()) + asmCode.dest(asmParser.dest()) + asmCode.jump(asmParser.jump()) << std::endl;
		}
	}
	
	outFile.close();
	return 0;
}
