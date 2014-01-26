/**
 * @author moshangcheng
 * @version 1.0
 * @date 2011-11-5 下午01:17:55
 * @brief http://acm.nankai.edu.cn/p1116.html
 */

#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;

string bigNumMulitply(const string& bigNum, int x) {
	int res = 0;
	string ans = "";
	for (int i = bigNum.size() - 1; i >= 0; i--) {
		int sum = res + (bigNum[i] - '0') * x;
		ans += (char) (sum % 10 + '0');
		res = sum / 10;
	}
	while (res > 0) {
		ans += (char) (res % 10 + '0');
		res /= 10;
	}
	reverse(ans.begin(), ans.end());
	return ans;
}

int main() {
	int n;
	while (cin >> n) {
		if (n <= 4) {
			cout << n << endl;
			continue;
		}
		int res = n % 3;
		int power = n / 3;
		if (res == 1) {
			power--;
			res += 3;
		}
		string ans = "1";
		for (int i = 0; i < power / 12; i++) {//3^12 == 531441
			ans = bigNumMulitply(ans, 531441);
		}
		for (int i = 0; i < power % 12; i++) {
			ans = bigNumMulitply(ans, 3);
		}
		if (res != 0) {
			ans = bigNumMulitply(ans, res);
		}
		cout << ans << endl;
	}
	return 0;
}
