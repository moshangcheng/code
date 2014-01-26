#include <iostream>
#include <sstream>
#include <string>
#include <cmath>
#include <algorithm>
using namespace std;

int main()
{
	string s;
	int i, n, flag, n_test;
	istringstream istr;
	int sum_a, sum_b, best_d, cnt_d, digit[11];
	cin >> n_test;
	getline(cin, s);
	while(n_test-- > 0)	{
		getline(cin, s);
		istr.clear();
		istr.str(s);
		sum_a = sum_b = 0;
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
		else	{
			best_d = 1000000000;
			flag = digit[0];
			if(digit[0] == 0)	
				swap(digit[0], digit[1]);
			do	{
				for(i = n/2; i < n; i++)
					if(digit[i] == flag)	break;
				if(i < n)	continue;
				sum_a = sum_b = 0;
				for(i = 0; 2*i < n; i++)
					sum_a = sum_a*10 + digit[i];
				for(; i < n; i++)
					sum_b = sum_b*10 + digit[i];
				cnt_d = abs(sum_a - sum_b);
				if(cnt_d < best_d)	best_d = cnt_d;
			}while(next_permutation(digit, digit+n));
		}
		cout << best_d << endl;
	}
	return 0;
}
