#include <iostream>
#include <fstream>
#include <string>
#include "parser.h"

void openFile(std::ifstream& file, std::string filename) {
	file.open(filename);
	
	if (!file) {
		std::cout << "Failed to open " << filename << ".\n";
	}
}

Parser::Parser(std::string filename) {
	openFile(file, filename);
}

//returns boolean if EOF reached
bool Parser::hasMoreCommands() {
	std::string nxt_line;
	if (file.eof()) return false;
	else return true;
}

//returns next line
std::string Parser::advance() {
	std::string curr_line;
	while (curr_line == "" || curr_line[0] == '/') {
		std::getline(file, curr_line);
	}
	return curr_line.substr(curr_line.find_first_not_of(" "));
}

//returns commandType
std::string Parser::commandType() {
	if (curr_command[0] == '@')				return "A_COMMAND";
	else if (curr_command[0] == '(')		return "L_COMMAND";
	else									return "C_COMMAND";
}

//returns symbol in address or label command
std::string Parser::symbol() {
	if (commandType() == "A_COMMAND") {
		return curr_command.substr(1);
	}
	else if (commandType() == "L_COMMAND") {
		return curr_command.substr(1, curr_command.length()-2);
	}
	return "NULL";
}

//returns dest mnemonic
std::string Parser::dest() {
	if (curr_command.find("=") == std::string::npos) return "null";
	else return curr_command.substr(0, curr_command.find("="));
}

//returns comp mnemonic
std::string Parser::comp() {
	int start_pos;
	if (curr_command.find("=") == std::string::npos) start_pos = 0;
	else start_pos = curr_command.find("=")+1;
	
	int end_pos;
	
	if (curr_command.find(";") != std::string::npos) end_pos = curr_command.find(";");
	else end_pos = curr_command.find_first_of(" ");
	
	return curr_command.substr(start_pos, end_pos-start_pos);
}

//returns jump mnemonic
std::string Parser::jump() {
	if (curr_command.find(";") == std::string::npos) return "null";
	else return curr_command.substr(curr_command.find(";")+1, curr_command.find_first_of(" ", curr_command.find(";")+1)-(curr_command.find(";")+1));
}

//return search pointer to beginning of ifstream file
void Parser::returnToBegin() {
	file.clear();
	file.seekg(0, std::ios::beg);
}
