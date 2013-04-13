/**
 * @author moshangcheng
 * @version 1.0
 * @date 2011-3-26 上午11:32:13
 * @brief http://acm.nankai.edu.cn/p1726.html
 */

#include <cmath>
#include <iostream>
using namespace std;

const double PI = 4.0 * atan(1.0);

inline double logFactorial(int n) {
	if (n == 0 || n == 1) {
		return 0;
	}
	//Stirling's approximation, from wiki
	return 0.5 * log(2.0 * PI * n) + n * log(1.0 * n) - n;
}

inline int logOddFactorial(int start, int end) {
	double min = logFactorial(end) - logFactorial(start)
			- logFactorial((end - 1) / 2) + logFactorial((start - 1) / 2)
			- (end - start) / 2 * log(2.0) + log(1.0 * start);
	min /= log(2.0);
	return ceil(min);
}

int main() {
	int caseNum;
	cin >> caseNum;
	while (caseNum-- > 0) {
		int start, end;
		cin >> start >> end;
		 if (start == end && end == 1) {
			 cout << 1 << endl;
			 continue;
		 }
		cout << logOddFactorial(start, end) << endl;
	}
}
