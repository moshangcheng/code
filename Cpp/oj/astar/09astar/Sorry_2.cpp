#include <cstdio>
#include <string>
using namespace std;

int TelNum[1000000];
string Number[1000000];
int Convert[10][10];


void int_to_string(int number, string& s)	{
	int i, j;
	s = "000000";
	for(i = 5; i >= 0; i--, number /= 10)
		s[i] = number%10+48;
}


int main()
{
	int i, j, k;
	
	int n, m;
	scanf("%d", &n);
	
	
	for(i = 0; i < n; i++)	{
		scanf("%d", TelNum+i);
		int_to_string(TelNum[i], Number[i]);
	}
	
	for(i = 0; i < 10; i++)
	for(j = 0; j < 10; j++)
		scanf("%d", Convert[i]+j);
	
	
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
				for(k = 0; k < 6; k++)
					t *= Convert[temp[k]-48][Number[j][k]-48];
				sum += t;
			}
		}
		printf("%d\n", sum);
	}
	return 0;
}
