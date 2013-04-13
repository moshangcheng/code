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
using namespace std;

int size;
char finalList[200];
int combine[26][26];
bool opposed[26][26];

void init()	{
	size = 0;
	for(int i = 0; i < 26; i++)	{
		for(int j = 0; j < 26; j++)	{
			combine[i][j] = -1;
			opposed[i][j] = 0;
		}
	}
}


void envolution(char c)	{
	if(size > 0)	{
		while(size > 0)	{
			int isCombined = combine[finalList[size-1]-'A'][c-'A'];
			if(isCombined < 0)	{
				break;
			}
			c = isCombined+'A';
			size--;
		}
		for(int j = 0; j < size; j++)	{
			if(opposed[finalList[j]-'A'][c-'A'])		{
				size = 0;
				return;
			}
		}
	}
	finalList[size++] = c;
}

int main()	{
//int tempTest(istream& cin, ostream& cout)	{
	int T, C, D, N;
	cin >> T;
	for(int i = 0; i < T; i++)	{
		init();
		cin >> C;
		string elementList;
		for(int j = 0; j < C; j++)	{
			char tempA, tempB, tempC;
			cin >> tempA >> tempB >> tempC;
			combine[tempA-'A'][tempB-'A'] = tempC-'A';
			combine[tempB-'A'][tempA-'A'] = tempC-'A';
		}
		cin >> D;
		for(int j = 0; j < D; j++)	{
			char tempA, tempB;
			cin >> tempA >> tempB;
			opposed[tempA-'A'][tempB-'A'] = true;
			opposed[tempB-'A'][tempA-'A'] = true;
		}
		cin >> N >> elementList;
		for(int j = 0; j < N; j++)	{
			envolution(elementList[j]);
		}
		cout << "Case #" << i+1 << ": [";
		for(int j = 0; j < size-1; j++)	{
			cout << finalList[j] << ", ";
		}
		if(size > 0)	{
			cout << finalList[size-1];
		}
		cout << "]\n";
	}
	return 0;
}
