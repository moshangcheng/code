#include <iostream>
using namespace std;

int x = 1;

#define a (x+1)

void printa() { int x = 2; cout << a << endl; }

int main() {
	printa();
	return 0;
}