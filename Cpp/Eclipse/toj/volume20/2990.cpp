#include <iostream>
using namespace std;

int a[200], b[200];

int main()
{
	int i, j, s, len_a, len_b, ntest;
	cin >> ntest;
	while(ntest-- > 0) {
		s = 0;
		cin >> len_a;
		for(i = 0; i < len_a; i++)
			cin >> a[i];
		cin >> len_b;
		for(i = 0; i < len_b; i++) {
			cin >> b[i];
			for(j = 0 ; j < len_a; j++)
				if(b[i] + a[j] == 0) s++;
		}
		cout << s << endl;
	}
	return 0;
}
