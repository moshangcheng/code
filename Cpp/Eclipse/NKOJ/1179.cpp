/**
 * @author moshangcheng
 * @version 1.0
 * @date 2011-3-18 下午10:25:39
 * @brief http://acm.nankai.edu.cn/p1179.html
 */
#include <iostream>
#include <string>
using namespace std;

long long GCD(long long a, long long b) {
	long long m;
	while (b) {
		m = a % b;
		a = b;
		b = m;
	}
	return a;
}

int main() {
	string c;
	long long int n, a, b, length, i;
	long long int tempn, tempa, mina, minn;
	while (cin >> c) {
		if (c[1] == '\0')
			break;
		n = 0;
		length = 1;
		for (i = 2; c[i] != '.' && c[i] != '\0'; i++, length *= 10)
			n = n * 10 + int(c[i] - 48);
		i = 10;
		while (i <= length) {
			tempn = n / i * i * (i - 1) + n % i * i;
			tempa = length * (i - 1);
			b = GCD(tempa, tempn);
			tempn = tempn / b;
			tempa = tempa / b;
			//cout<<tempa<<" "<<tempn<<" "<<n<<endl;
			if (int(double(tempn) / tempa * length) - n < 10) {
				if (i == 10) {
					mina = tempa;
					minn = tempn;
				} else if (tempa < mina) {
					mina = tempa;
					minn = tempn;
				}
			}
			i *= 10;
		}
		cout << minn << "/" << mina << endl;
	}
	return 0;
}
