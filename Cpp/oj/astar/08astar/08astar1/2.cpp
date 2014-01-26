#include <iostream>
#include <string>
using namespace std;

int s[200];
string suba[200], subb[200];


int main()
{
	string a, b;
	int i, j, lena, lenb;
	while(cin >> a >> b)	{
		for(i = 0; i < 200; i++)	{
			suba[i].clear();
			subb[i].clear();
		}
		for(i = lena = 0; i < a.size(); lena++) {
			if(a[i] > 0) {
				while(i < a.size() && a[i] > 0)	
					suba[lena] += a[i++];
			}
			else {
				suba[lena] = a[i++];
				suba[lena] += a[i++];
			}
		}
		for(i = lenb = 0; i < b.size(); lenb++) {
			if(b[i] > 0) {
				while(i < b.size() && b[i] > 0)	
					subb[lenb] += b[i++];
			}
			else {
				subb[lenb] = b[i++];
				subb[lenb] += b[i++];
			}
		}
	}
	return 0;
}
