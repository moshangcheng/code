#include <iostream>
using namespace std;

class Solution {
public:
	int myFindFuc(int k, int A[], int m, int B[], int n) {
		if(m == 0) {
			return B[k];
		}
		else if(n == 0) {
			return A[k];
		}
		else if(k == 0) {
			return A[0] < B[0] ? A[0] : B[0];
		}

		int iA, iB;
		int aver = k / 2;
		if(m <= aver) {
			iA = m - 1;
			iB = k - m;
		}
		else if(n <= aver) {
			iB = n - 1;
			iA = k - n;
		}
		else {
			iA = aver;
			iB = k - aver;
		}
		if(A[iA] <= B[iB]) {
			return myFindFuc(k - iA - 1, A + iA + 1, m - iA - 1, B, iB + 1);
		}
		else if(A[iA] > B[iB]) {
			return myFindFuc(k - iB - 1, A, iA + 1, B + iB + 1, n - iB - 1);
		}
	}

    double findMedianSortedArrays(int A[], int m, int B[], int n) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
		if( (m+n) % 2 == 0) {
			return (myFindFuc((m+n)/2, A, m, B, n) + myFindFuc((m+n+1)/2, A, m, B, n) ) / 2.0;
		}
		else {
			return myFindFuc((m+n)/2, A, m, B, n);
		}
    }
};

int main() {
	cout << atoi("12a") << endl;
	const int SIZE_A = 2;
	const int SIZE_B = 2;
	int A[SIZE_A];
	int B[SIZE_B];
	for(int i = 0; i < SIZE_A; i++) {
		//A[i] = 2 * i + 1;
	}
	A[0] = B[0] = B[1] = 1;
	A[1] = 2;
	for(int i = 0; i < SIZE_B; i++) {
		//B[i] = 2 * (i + 1);
	}

	Solution s;
	cout << s.findMedianSortedArrays(A, SIZE_A, B, SIZE_B) << endl;
	return 0;
}
