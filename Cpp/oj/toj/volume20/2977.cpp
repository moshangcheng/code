#include <iostream>
#include <string>
using namespace std;

int main()
{
	char c, u;
	int i, cr, cy, w, n;
	while(cin >> n && n > 0)  {
		cr = cy = 0;
		for(i = 0; i < n; i++) {
			cin >> c;
			if(c == 'R')		cr++;
			else if(c == 'Y') 	cy++;
			else if(c == 'B')	w = (cr != 7);
			else if(c == 'L')   w = (cy == 7);
		}
		if(w == 0)  cout << "Red\n";
		else 		cout << "Yellow\n";
	}
	return 0;
}
