#include <iostream>
#include <fstream>
using namespace std;

const int SIZE = 10000;

int main()
{
	int A[SIZE], B[SIZE];
	ofstream out("in.txt");
	for(int i = 0; i < SIZE; i++)	{
		if(i == 0)	{
			A[0] = 0;
			B[0] = 1;
		}
		else {
			srand(time(NULL));
			A[i] = rand() % RAND_MAX * 2 + A[i-1];
			B[i] = rand() % RAND_MAX * 2 + B[i-1];
		}
	}
	for(int i = 0; i < SIZE; i++)	out << A[i] << " ";
	out << endl << endl << endl;
	for(int i = 0; i < SIZE; i++)	out << B[i] << " ";
	return 0;
}
