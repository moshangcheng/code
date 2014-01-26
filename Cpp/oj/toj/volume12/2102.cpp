#include <iostream>
#include <string>
using namespace std;

int main()
{
	string s;
	int i, j, n, m;
	char c, c1, c2;
	while(cin >> c1 >> n >> c2 >> m)	{
		if(n == 0 && m == 0)	break;
		for(s.clear(), m--; m >= 0; m = m/26-1)
			s += m%26 + 'A';
		for(j = s.size()-1, i = 0; i < j; i++, j--) {
			char c = s[i];
			s[i] = s[j];
			s[j] = c;
		}
		cout << s << n << endl;
	}
	return 0;
}
