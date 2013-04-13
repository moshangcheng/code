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
#include <algorithm>
using namespace std;

int lcmArrayLength;
int gcdArrayLength;
long long N, L, H;
vector<long long> notes, realNotes;
long long lcmArray[10001];
long long gcdArray[10001];

long long gcd(long long a, long long b) {
	while (a != 0) {
		long long c = b % a;
		b = a;
		a = c;
	}
	return b;
}

long long lcm(long long a, long long b) {
	double ans = 1.0 * a / gcd(a, b) * b;
	if (ans > H - 0.01) {
		return 0;
	}
	return a / gcd(a, b) * b;
}

long long minDivisor(long long a) {
	long long start, end;
	if (a <= H) {
		return a;
	}
	if (H - L > 100000000) {
		start = (a + H - 1) / H;
		end = a / L;
	} else {
		start = L;
		end = H;
	}
	for (long long i = start; i <= end; i++) {
		if (a % i == 0) {
			return i;
		}
	}
	return 0;
}

long long minMultiple(long long a) {
	if (a >= L) {
		return a;
	}
	if (H - L >= a) {
		return (L + a - 1) / a * a;
	}
	return 0;
}

int tempTest(istream& cin, ostream& cout) {
	//int main()	{
	long long T;
	cin >> T;
	for (long long i = 0; i < T; i++) {
		notes.clear();
		realNotes.clear();
		cin >> N >> L >> H;
		for (long long j = 0; j < N; j++) {
			long long tempValue;
			cin >> tempValue;
			notes.push_back(tempValue);
		}
		sort(notes.begin(), notes.end());
		realNotes.push_back(notes[0]);
		long long lastValue = notes[0];
		for (long long j = 0; j < N; j++) {
			if (lastValue != notes[j]) {
				realNotes.push_back(notes[j]);
				lastValue = notes[j];
			}
		}
		N = realNotes.size();
		//������С����������
		lcmArrayLength = 0;
		long long cntLCM = 1;
		for (int j = 0; j < N; j++, lcmArrayLength++) {
			lcmArray[j] = lcm(cntLCM, realNotes[j]);
			if (lcmArray[j] == 0) {
				break;
			}
			cntLCM = lcmArray[j];
		}
		//�������Լ������
		gcdArrayLength = 0;
		long long cntGCD = realNotes[N - 1];
		for (int j = N - 1; j >= 0; j--, gcdArrayLength++) {
			gcdArray[j] = gcd(realNotes[j], cntGCD);
			if (gcdArray[j] < L) {
				break;
			}
			cntGCD = gcdArray[j];
		}

		long long value = 0;
		for (int j = N - gcdArrayLength; j <= lcmArrayLength; j++) {
			if (j == 0) {
				value = minDivisor(gcdArray[j]);
			} else if (j == N) {
				value = minMultiple(lcmArray[j - 1]);
			} else {
				if (gcdArray[j] % lcmArray[j - 1] == 0) {
					value = lcmArray[j - 1];
					break;
				}
			}
		}
		if (value == 0) {
			cout << "Case #" << i + 1 << ": NO\n";
		} else {
			cout << "Case #" << i + 1 << ": " << value << "\n";
		}
	}
	return 0;
}
