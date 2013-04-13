//02-06-08 10:28
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int convert(char c)
{
	if(c <= '9' && c >= '0')		return c - 48;
	else if(c <= 'Z' && c >= 'A')	return c - 55;
	else if(c <= 'z' && c >= 'a')	return c - 61;
}

char inconvert(int n)
{
	if(n <= 9 && n >= 0)		return n + 48;
	else if(n <= 35 && n >= 10)	return n + 55;
	else if(n <= 61 && n >= 36)	return n + 61;
}

int main()
{
	int len, digit[100];
	string in_str, out_str;
	int i, j, s, n, in_base, out_base;
	while(cin >> n) {
		for(i = 0; i < n; i++)	{
			cin >> in_base >> out_base >> in_str;
			out_str.clear();
			len = in_str.size();
			for(j = 0; j < len; j++)
				digit[len-1-j] = convert(in_str[j]);
			while(len > 0)	{
				s = 0;
				for(j = len-1; j >= 0; j--)	{
					s = s*in_base + digit[j];
					digit[j] = s / out_base;
					s = s % out_base;
				}
				out_str += inconvert(s);
				while(len > 0 &&digit[len-1] == 0)	len--;
			}
			reverse(out_str.begin(), out_str.end());
			cout << out_base << " " << out_str << endl;
			if(i < n-1)	cout << endl;
		}
	}
	return 0;
}
