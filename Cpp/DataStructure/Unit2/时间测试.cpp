#include<iostream>
#include<ctime>
using namespace std;

int main() {
	float seconds;
	clock_t start, finish;
	start = clock();
	for (int i = 0; i < 100000000; i++)
		;
	finish = clock();
	seconds = (finish - start) / CLK_TCK;
	cout << start << " " << finish << " " << CLK_TCK << " " << seconds << endl;
	system("pause");
	return 0;
}

