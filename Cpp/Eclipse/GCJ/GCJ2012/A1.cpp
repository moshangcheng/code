#include <cstdio>
#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

int main() {
	ifstream in("C:\\Users\\shu\\Desktop\\in.txt");
	ofstream out("C:\\Users\\shu\\Desktop\\out.txt");

	int T;
	in >> T;
	for(int i = 1; i <= T; i++) {
		int A, B;
		in >> A >> B;
		vector<double> cp;
		cp.push_back(1);
		for(int j = 1; j <= A; j++) {
			double v;
			in >> v;
			cp.push_back(cp[j-1] * v);
		}
		double minSum, retypeSum, continueSum, backSum;
		minSum = continueSum = (B - A + 1) + (1 - cp[A]) * (B + 1);
		retypeSum = 2 + B;
		if(retypeSum < minSum) {
			minSum = retypeSum;
		}
		for(int j = A-1; j > 0; j--) {
			backSum = (A - j) * 2 + (B - A + 1) + (1 - cp[j]) * (B + 1);
			if(backSum < minSum) {
				minSum = backSum;
			}
		}
		out.setf(ios::fixed);
		out.precision(6);
		out << "Case #" << i << ": " << minSum << endl;
	}
	return 0;
}