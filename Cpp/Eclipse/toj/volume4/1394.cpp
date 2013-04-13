#include <iostream>
#include <string>
using namespace std;

int period[1000000], p[1000000];

int main()
{
	string s;
	int i, j;
	while(cin >> s) {
		if(s == ".")	break;
		period[0] = 1;	p[0] = -1;
		for(j = -1, i = 1; i < s.size(); i++) {
			while(j > -1 && s[j+1] != s[i])  j = p[j];
			if(s[j+1] == s[i]) j++;
			p[i] = j;
			if(j == -1)	period[i] = i+1;
			else if(period[i-j-1] != period[j]) 
					period[i]= i+1;
			else	period[i] = period[j];
		}
		cout << s.size()/(period[s.size()-1]) << endl;
	}
	return 0;
}

		
