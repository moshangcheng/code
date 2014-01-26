#include <iostream>
#include <cmath>
using namespace std;

int main()
{
	int i, j;
	int n, m, sum, bound;
	int ntest, otest = 0;
	cin >> ntest;
	while(otest++ < ntest)	{
		cin >> n;
		bound = floor(sqrt(n));
		sum = 1;
		for(i = 2, m = n; i <= bound; i++)	{
			if(m%i != 0)	continue;
			for(j = 0; m % i == 0; j++)	m /= i;
			sum *= 1 + 2*j;
			bound = floor(sqrt(m));
		}
		if(m != 1)	sum *= 3;
		sum = (sum+1)/2;
		cout << "Scenario #" << otest << ":\n";
		cout << sum << endl << endl;
	}
	return 0;
}
