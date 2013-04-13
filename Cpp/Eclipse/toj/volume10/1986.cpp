#include <iostream>
#include <sstream>
#include <string>
#include <cmath>
using namespace std;

int digit[11], status[11];
int n, sum_a, sum_b, best_d;

void dfs(int depth)	{
	if(depth == n)	{
		if(abs(sum_a - sum_b) < best_d)
			best_d = abs(sum_a - sum_b);
		return;
	}
	else {
		int i, j;
		for(i = 0; i < n; i++)	{
			if(status[i] != 0)	continue;
			if(digit[i] == 0 && sum_a == 0)	continue;
			status[i] = 1;
			sum_a = sum_a*10 + digit[i];
			for(j = 0; j < n; j++)	{
				if(status[j] != 0)	continue;
				if(digit[j] == 0 && sum_b == 0)	continue;
				status[j] = -1;
				sum_b = sum_b*10 + digit[j];
				dfs(depth+2);
				sum_b /= 10;
				status[j] = 0;
			}
			sum_a /= 10;
			status[i] = 0;
		}
	}
}

int main()
{
	string s;
	int i, n_test;
	istringstream istr;
	cin >> n_test;
	getline(cin, s);
	while(n_test-- > 0)	{
		getline(cin, s);
		istr.clear();
		istr.str(s);
		sum_a = sum_b = 0;
		best_d = 1000000000;
		memset(status, 0, sizeof(status));
		for(n = 0; istr >> digit[n]; n++);
		if(n == 1)	continue;
		if((n&1) == 1)	{
			if(digit[0] != 0)	
				sum_a = digit[0]*10 + digit[1];
			else 				
				sum_a = digit[1]*10 + digit[0];
			for(i = 2; 2*i <= n; i++)
				sum_a = sum_a*10 + digit[i];
			for(i = n-1; 2*i > n; i--)
				sum_b = sum_b*10 + digit[i];
			best_d = abs(sum_b - sum_a);
		}
		else	if(n == 2)
			best_d = digit[1] - digit[0];
		else	dfs(0);
		cout << best_d << endl;
	}
	return 0;
}
