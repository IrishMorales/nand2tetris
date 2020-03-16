#include <iostream>
#include <string>
using namespace std;

int main() {
	/*
	for (int i=0; i<16; ++i) {
		std::cout << "Bit(in=in[" << i << "], load=load, out=out[" << i << "]);\n";
	}
	for (int i=0; i<8; ++i) {
		std::cout << "Register(in=in, load=load" << i << ", out=out" << i << ");\n";
	}
	*/
	for (int i=0; i<=15; ++i) {
		std::cout << "{\"R"<< i << "\"," << i << "},\n";
	}
}
