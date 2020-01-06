#include <iostream>
#include <algorithm>
#include <unordered_map>
#include "symbolTable.h"

SymbolTable::SymbolTable() {
	symbol_map = {
		{"R0",0},
		{"R1",1},
		{"R2",2},
		{"R3",3},
		{"R4",4},
		{"R5",5},
		{"R6",6},
		{"R7",7},
		{"R8",8},
		{"R9",9},
		{"R10",10},
		{"R11",11},
		{"R12",12},
		{"R13",13},
		{"R14",14},
		{"R15",15},
		{"SCREEN",16384},
		{"KBD",24576},
		{"SP",0},
		{"LCL",1},
		{"ARG",2},
		{"THIS",3},
		{"THAT",4},
	};
}

void SymbolTable::addEntry(std::string symbol, int address) {
	symbol_map[symbol] = address;
}

bool SymbolTable::contains(std::string symbol) {
	if (symbol_map.find(symbol) != symbol_map.end()) return true;
	else return false;
}

int SymbolTable::getAddress(std::string symbol) {
	return symbol_map[symbol];
}

void SymbolTable::print_map() {
	std::for_each(symbol_map.begin(), symbol_map.end(),
        [](const std::pair<std::string, int> &p) {
        	std::cout << "{" << p.first << ": " << p.second << "}\n";
        });
}
