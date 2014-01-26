#include <map>
#include <cmath>
#include <cstdio>
#include <string>
#include <iostream>
using namespace std;

const int MAX = 5005;

string s[MAX];
int Psblty[MAX][MAX];
int TelNum[1000000];
string Number[1000000];
int Convert[10][10];
//map<int, int> int_int;
//map<string, int> string_int;

void int_to_string(int number, string& s)	{
	int i, j;
	s = "000000";
	for(i = 5; i >= 0; i--, number /= 10)
		s[i] = number%10+48;
}

void sort_string(string& s)	{
	int i, j;
	for(i = 1; i < 6; i++)	{
		int temp = s[i];
		for(j = i-1; j >= 0 && s[j] > temp; j--)
			s[j+1] = s[j];
		s[j+1] = temp;
	}
}

int string_to_int(const string& s)	{
	int sum;
	for(int i = 0; i < 6; i++)	
		sum += sum*10 + s[i]-48;
	return sum;
}

int main()
{
	int i, j, k;
		
	/*s[0] = "000000";
	string_int[s[0]] = 1;
	for(i = 1; i < MAX; i++)	{
		s[i] = s[i-1];
		for(j = 5; j >= 0; j--)
			if(s[i][j]-48 < 9)	break;
		if(j < 0)	break;
		s[i][j]++;
		for(j++; j < 6; j++)	s[i][j] = s[i][j-1];
		string_int[s[i]] = i+1;
	}*/

	int n, m;
	scanf("%d", &n);
	
	
	for(i = 0; i < n; i++)	{
		scanf("%d", TelNum+i);
		int_to_string(TelNum[i], Number[i]);
		//int_int[TelNum[i]]++;
	}
	
	for(i = 0; i < 10; i++)
	for(j = 0; j < 10; j++)
		scanf("%d", Convert[i]+j);
	
	/*for(i = 0; i < MAX; i++)
	for(j = 0; j < MAX; j++)	{
		Psblty[i][j] = 1;
		for(int k = 0; k < 6; k++)
			Psblty[i][j] *= Convert[s[i][k]-48][s[j][k]-48];
	}*/
	
	scanf("%d", &m);
	for(i = 0; i < m; i++)	{
		int DilNum;
		scanf("%d", &DilNum);
		string temp;
		int_to_string(DilNum, temp);
		
		int p = 1, sum = 0;
		for(j = 0; j < n; j++)	{
			if(TelNum[j] != DilNum)	{
				int t = 1;
				for(int k = 0; k < 6; k++)
					t *= Convert[temp[k]-48][Number[j][k]-48];
				sum += t;
			}
		}
					
		/*sort_string(temp);
		int index = string_int[temp]-1;
		int sum;
		map<int, int>::iterator cnt;
		for(cnt = int_int.begin(); cnt != int_int.end(); cnt++)	{
			int t = 1;
			for(j = 0; j < 6; j++) t *= Convert[
		int p = floor(Psblty[index][index]/1.0/sum*1000000+0.5);*/
		printf("%d\n", sum);
	}
	return 0;
}
