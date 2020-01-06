#include <iostream>
#include <algorithm>
#include <unordered_map>

class SymbolTable {
	private:
		std::unordered_map<std::string, int> symbol_map;
	public:
		SymbolTable();
		void addEntry(std::string symbol, int address);
		bool contains(std::string symbol);
		int getAddress(std::string symbol);
		void print_map();
};
