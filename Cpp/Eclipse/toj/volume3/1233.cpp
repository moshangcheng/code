#include <iostream>
using namespace std;

inline int f(int m, int n)
{
	return (4*(m/2) + (m&1));
}

int main()
{
	int ntest, m, n;
	cin >> ntest;
	while(ntest-- > 0)	{
		cin >> m >> n;
		if(m == n)
			cout << f(m, n) << endl;
		else if(m == n+2)
			cout << f(m, m)-2 << endl;
		else 
			cout << "No Number\n";
	}
	return 0;
}
			
