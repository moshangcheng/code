#include <iostream>
using namespace std;

int main()
{
	int ntest;
	int i, j, sum;
	long long N, L, W, P, S, T;
	cin >> ntest;
	while(ntest-- > 0) {
		cin >> N >> L >> W;
		sum = 0;
		for(i = 0; i < N; i++) {
			cin >> P >> S;
			if(P*W <= L*(W-S)) sum++;
		}
		cout << sum << endl;
	}
	return 0;
}
