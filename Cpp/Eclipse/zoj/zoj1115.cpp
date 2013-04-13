/**
 * @author moshangcheng
 * @version 1.0
 * @date 2011-3-25 下午02:48:40
 * @brief http://acm.zju.edu.cn/onlinejudge/showProblem.do?problemCode=1115
 */
#include <iostream>
#include <string>
using namespace std;

int main() {
	string number;
	int digitSum;
	while (cin >> number && number != "0") {
		digitSum = 0;
		for (int i = 0; i < number.size(); i++) {
			digitSum += number[i] - '0';
		}
		while (digitSum > 9) {
			int temp;
			for (temp = 0; digitSum > 0; digitSum /= 10) {
				temp += digitSum % 10;
			}
			digitSum = temp;
		}
		cout << digitSum << endl;
	}
	return 0;
}
