#include <iostream>
using namespace std;
#include "LinkedQueue.h"

void Output(int& minH, int& minQ, LinkedQueue<int>* H, int k, int n) {
	int c;
	H[minQ].Delete(c);
	cout << "Move car " << minH << " from holding track " << minQ
			<< " to output" << endl;
	minH = n + 2;
	for (int i = 1; i <= k; i++)
		if (!H[i].IsEmpty() && (c = H[i].First()) < minH) {
			minH = c;
			minQ = i;
		}
}

bool Hold(int c, int& minH, int &minQ, LinkedQueue<int>* H, int k) {
	int BestTrack = 0, BestLast = 0, x;
	for (int i = 1; i <= k; i++)
		if (!H[i].IsEmpty()) {
			x = H[i].Last();
			if (c > x && x > BestLast) {
				BestLast = x;
				BestTrack = i;
			}
		} else if (!BestTrack)
			BestTrack = i;
	if (!BestTrack)
		return false;
	H[BestTrack].Add(c);
	cout << "Move car " << c << " from input " << "to holding track "
			<< BestTrack << endl;
	if (c < minH) {
		minH = c;
		minQ = BestTrack;
	}
	return true;
}

bool Railroad(int*p, int n, int k) {
	LinkedQueue<int>* H = new LinkedQueue<int> [k--];
	int NowOut = 1;
	int minH = n + 1;
	int minQ;
	for (int i = 0; i < n; i++)
		if (p[i] == NowOut) {
			cout << "Move car " << p[i] << " from input to output" << endl;
			NowOut++;
			while (minH == NowOut) {
				Output(minH, minQ, H, k, n);
				NowOut++;
			}
		} else {
			if (!Hold(p[i], minH, minQ, H, k))
				return false;
		}
	return true;
}

int main() {
	int n, m;
	cin >> n >> m;
	int*a = new int[n];
	for (int i = 0; i < n; i++)
		cin >> a[i];
	if (!Railroad(a, n, m))
		cout << "No Solutions!\n";
	else
		cout << "Problem solved!\n";
	delete[] a;
	system("pause");
	return 0;
}

