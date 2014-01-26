#include <iostream>
#include <string>
#include <map>
using namespace std;

typedef long long int ll;

map<ll> s[11];
map<ll>::iterator cnt, prev;

int inline convert(char c)
{
	if(c >= '0' && c <= '9')	return (c-48);
	else						return (c-'A');
}

ll dec(const string& s)
{
	ll sum = 0;
	for(int i = s.size()-1; i >= 0; i--)
		sum += sum*16 + convert(s[i]);
	return sum;
}

int main()
{
	int i, j, k;
	ll k, x, y;
	string S, K, X, Y;
	while(cin >> S >> X >> Y) {
		for(i = 0; i < 11; i++)	s[i].clear();
		s[0] = 1;
		x = dec(X);
		y = dec(Y);
		k = dec(K);
		for(i = 1; i < 11; i++)	{
			for(cnt = s[i-1].begin(); cnt != s[i-1].end(); cnt++)
			for(j = 0; j < S.size(); j++)
				s[i][(*cnt)+convert(S[j])]++;
		}
		
			
