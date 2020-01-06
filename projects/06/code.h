#include <iostream>
#include <unordered_map>

class Code {
	private:
		std::unordered_map<std::string, std::string> dest_map;
	    std::unordered_map<std::string, std::string> comp_map;
	    std::unordered_map<std::string, std::string> jump_map;
	    
	public:
		Code();
		std::string dest(std::string str);
		std::string comp(std::string str);
		std::string jump(std::string str);
};
