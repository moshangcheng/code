#include <iostream>
using namespace std;

int main()
{
	int i, r, e, c, n;
	while(cin >> n)	{
		for(i = 0; i < n; i++)	{
			cin >> r >> e >> c;
			if(r + c > e)
				cout << "do not advertise\n";
			else if(r + c == e)
				cout << "does not matter\n";
			else 
				cout << "advertise\n";
		}
	}
	return 0;
}
