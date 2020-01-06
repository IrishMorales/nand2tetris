#include <iostream>
#include <fstream>
#include <string>

void openFile(std::ifstream& file, std::string filename);

class Parser {
	public:
		std::ifstream file;
		std::string curr_command;
		
		Parser(std::string filename);
		bool hasMoreCommands();
		std::string advance();
		std::string commandType();
		std::string symbol();
		std::string dest();
		std::string comp();
		std::string jump();
		void returnToBegin();
};
