#include <iostream>
using namespace std;

int main() {
	int n, a[100];
	cin >> n;
	for (int i = 0; i < n; i++)
		cin >> a[i];

	/*int sum=0, maxSum=0;
	 for(int i = 0; i < n; i++) {
	 sum += a[i];
	 if (sum < 0) sum = 0;
	 if (sum > maxSum) maxSum = sum;
	 }

	 cout << maxSum << endl;*/

	int sum = 0, maxSum = 0, noSeq = 0, noStart = 1;
	for (int i = 0; i < n; i++) {
		sum += a[i];
		if (sum < 0) {
			sum = 0;
			noStart = 0;
		}
		if (sum == 0)
			noStart++;
		if (sum > maxSum) {
			maxSum = sum;
			noSeq = 0;
		}
		if (sum == maxSum)
			noSeq += noStart;
	}

	cout << maxSum << " " << noSeq << endl;

	system("pause");
	return 0;
}

