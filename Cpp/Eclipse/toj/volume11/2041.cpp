#include <iostream>
#include <cmath>
using namespace std;

int gcd(int a, int b)
{
    while(a != 0) {
        int c = b % a;
        b = a;
        a = c;
    }
    return b;
}

int main()
{
	int i = 0, p, q, n, m, d, prev_p, prev_q;
	while(cin >> n >> m)	{
		if(i++ > 0)	cout << endl;
		d = gcd(n, m);
		n /= d;		m /= d;
		prev_p = floor(1.0*n/m+0.5);	prev_q = 1;
		cout << prev_p << '/' << prev_q << endl;
		for(q = 2; q <= m; q++)	{
			p = floor(1.0*n*q/m+0.5);
			if(abs(n*q-p*m)*prev_q < abs(n*prev_q-m*prev_p)*q)	{
				cout << p << "/" << q << endl;
				prev_p = p;
				prev_q = q;
			}
		}
	}
	return 0;
}
