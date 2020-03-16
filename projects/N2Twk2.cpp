#include <iostream>
#include <string>
using namespace std;

int main() {
	string lastOut = "carry1";
	for (int i=1; i<16; ++i) {
		std::cout << "FullAdder (a=a[" << i << "], b=b[" << i << "], c=carry" << i-1 << ", sum=out[" << i << "], carry=carry" << i << "); \n";
	}
}
