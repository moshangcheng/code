#include <iostream>
#include "LinkedStack.h"
using namespace std;

void Output(int& minH, int& minS, LinkedStack<int>*H, int k, int n) {
	int c;
	H[minS].Delete(c);
	cout << "Move car " << minH << " from holding track ";
	cout << minS << " to output" << endl;
	minH = n + 2;
	for (int i = 1; i <= k; i++)
		if (!H[i].IsEmpty() && (c = H[i].Top()) < minH) {
			minH = c;
			minS = i;
		}
}

bool Hold(int c, int& minH, int& minS, LinkedStack<int>*H, int k, int n) {
	int BestTrack = 0;
	int BestTop = n + 1, x;
	for (int i = 1; i <= k; i++)
		if (!H[i].IsEmpty()) {
			x = H[i].Top();
			if (c < x && x < BestTop) {
				BestTop = x;
				BestTrack = i;
			}
		} else if (!BestTrack)
			BestTrack = i;
	if (!BestTrack)
		return false;
	H[BestTrack].Add(c);
	cout << "Move car " << c << " from input to holding track ";
	cout << BestTrack << endl;
	if (c < minH) {
		minH = c;
		minS = BestTrack;
	}
	return true;
}

bool Railroad(int*p, int n, int k) {
	LinkedStack<int>* H = new LinkedStack<int> [k + 1];
	int NowOut = 1;
	int minH = n + 1;
	int minS;
	for (int i = 0; i < n; i++)
		if (p[i] == NowOut) {
			cout << "Move car " << p[i] << " from input to output" << endl;
			NowOut++;
			while (minH == NowOut) {
				Output(minH, minS, H, k, n);
				NowOut++;
			}
		} else {
			if (!Hold(p[i], minH, minS, H, k, n))
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

