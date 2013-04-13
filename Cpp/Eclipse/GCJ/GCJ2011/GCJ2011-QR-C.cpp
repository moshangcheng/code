/********************************************************************
@created:	2011/05/05 17:16
@author:	moshangcheng
@version:	1.0
@tag:		GCJ2011
@purpose:	http://code.google.com/codejam/contest/dashboard?c=975485#s=p1
*********************************************************************/
#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <memory>
using namespace std;

const int SIZE = 1000;
const int MAX = 1<<20;

int candy[SIZE];

int main()	{
//int tempTest(istream& cin, ostream& cout)	{
	int T, N;
	cin >> T;
	for(int i = 0; i < T; i++)	{
		cin >> N;
		int minCandy = MAX, addSum = 0, xorSum = 0;
		for(int j = 0; j < N; j++)	{
			cin >> candy[j];
			addSum += candy[j];
			xorSum ^= candy[j];
			if(minCandy > candy[j])	{
				minCandy = candy[j];
			}
		}
		cout << "Case #" << i+1 << ": ";
		if(xorSum != 0)	{
			cout << "NO\n";
		}
		else	{
			cout << addSum - minCandy << "\n";
		}
	}
	return 0;
}
