#include <iostream>
using namespace std;

long long int s[19][201];

int main()
{
	int n, m, i, j, k;
	memset(s, 0, sizeof(s));
	s[1][0] = 1;
	for(i = 2; i < 19; i++)
	for(j = 0; j < 201; j++)
	for(k = 0; k < i && k <= j; k++)
		s[i][j] += s[i-1][j-k];
	while(cin >> n >> m) {
		if(n == 0 && m == 0) break;
		cout << s[n][m] << endl;
	}
	return 0;
}
		
