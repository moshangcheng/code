/********************************************************************
 @created:	2011/05/05 17:16
 @author:	moshangcheng
 @version:	1.0
 @tag:		GCJ2011
 @purpose:	http://code.google.com/codejam/
 *********************************************************************/
#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <memory>
using namespace std;

long long N, L, H;
long long notes[10000];

//int tempTest(istream& cin, ostream& cout)	{
int main() {
	long long T;
	cin >> T;
	for (long long i = 0; i < T; i++) {
		cin >> N >> L >> H;
		for (long long j = 0; j < N; j++) {
			cin >> notes[j];
		}
		long long value = -1;
		for (long long j = L; j <= H; j++) {
			bool flag = true;
			for (long long k = 0; k < N; k++) {
				if (notes[k] % j != 0 && j % notes[k] != 0) {
					flag = false;
					break;
				}
			}
			if (flag) {
				value = j;
				break;
			}
		}
		if (value == -1) {
			cout << "Case #" << i + 1 << ": NO\n";
		} else {
			cout << "Case #" << i + 1 << ": " << value << "\n";
		}
	}
	return 0;
}
