#include <iostream>
#include <fstream>
#include <math.h>
using namespace std;

const int MAX_RAND = 256;

int main() {
	int N;
	cout << "Please Enter the length of documents:\n";
	cin >> N;
	ofstream out("in.txt");
	for (int i = 0; i < N; i++)
		out.put(char(rand() % MAX_RAND));
	return 0;
}
