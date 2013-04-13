#include <iostream>
#include <cmath>
using namespace std;

const int MAX = 7;
long long sum[7], a[7], base[7];
long long power[10] = {1, 10, 100, 1000, 10000, 100000, 
				1000000, 10000000, 100000000, 1000000000};


int main()
{
	long long i, j, n, ntest;
	long long r, s, u, v, x, y;
	base[0] = sum[0] = a[0] = 0;
	for(i = 1; i < MAX; i++)	{
		base[i] = i*power[i] - (power[i]-1)/9;
		a[i] = base[i-1]*9*power[i-1]+i*9*power[i-1]*(9*power[i-1]+1)/2;
		sum[i] = sum[i-1] + a[i];
	}
	cin >> ntest;
	while(ntest-- > 0)	{
		cin >> n;
		for(r = 0; r < MAX && n > sum[r]; r++);
		n -= sum[r-1];
		s = ceil((sqrt((r+2*base[r-1])*(r+2*base[r-1])+8*r*n)-r-2*base[r-1])/2/r);
		n -= base[r-1]*(s-1) + r*s*(s-1)/2;
		for(u = 0; u < MAX && n > base[u]; u++);
		n -= base[u-1];
		x = (n+u-1)/u;	y = (n-1)%u+1;
		cout << (power[u-1] + x-1)%power[u+1-y]/power[u-y] << endl;
	}
	return 0;
}
