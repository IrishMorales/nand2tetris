#include <iostream>
#include <string>
using namespace std;

int main() {
	/*
	for (int i=0; i<16; ++i) {
		std::cout << "\nOr (a=a[" << i << "], b=b[" << i << "], out=out[" << i << "]);";
	}
	
	for (int i=0; i<16; ++i) {
		std::cout << "\nMux(a=a[" << i << "], b=b[" << i << "], sel=sel, out=out[" << i << "]);";
	}
	*/
	
	std::cout << "Or (a=in[0], b=in[1], out=In0orIn1);\n";
	string lastOut = "In0orIn1";
	for (int i=2; i<8; ++i) {
		string nextOut = "In" + to_string(i-1) + "orIn" + to_string(i);
		std::cout << "Or (a=" << lastOut << ", b=in[" << i << "], out=" << nextOut << ");\n";
		lastOut = nextOut;
	}
}
