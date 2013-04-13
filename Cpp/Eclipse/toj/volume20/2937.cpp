#include <iostream>
#include <algorithm>
using namespace std;

int cost[20000];

int main()
{
	int i, j, n, s, ntest;
	cin >> ntest;
	while(ntest-- > 0) {
		cin >> n;
		s = 0;
		for(i = 0; i < n; i++) 
			cin >> cost[i];
		sort(cost, cost + n);
		for(i = n%3; i < n; i += 3)
			s  += cost[i];
		cout << s << endl;
	}
	return 0;
}
