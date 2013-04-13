/**
 * @author moshangcheng
 * @version 1.0
 * @date 2011-4-15 下午05:53:00
 * @brief 高精度 莫比乌斯变换  循环多重集
 * @details http://acm.tju.edu.cn/toj/showp2795.html
 * 			http://hi.baidu.com/ly8666/blog/item/ac639e359dbeb9a65fdf0e53.html
 */
#include <iostream>
#include <string>
#include <cmath>
using namespace std;

const int MAXSIZE = 10000;
const int BASE = 10000;

class BigInt {
public:
	BigInt(int l = 1) {
		len = l;
		memset(s, 0, sizeof(s));
	}
	BigInt(const BigInt& b);
	string tostring() const;
	BigInt& operator =(const BigInt &b);
	BigInt& operator =(const string& str);
	int& operator [](int index) {
		return s[index];
	}
	BigInt operator +(const BigInt &b) const; //高精度加法
	BigInt operator *(int b) const;//高精度*单精度
	BigInt divide(int b, int &d) const;
private:
	int len;
	int s[MAXSIZE];
};

int EulerPHI(int n) {
	if (n == 1)
		return 1;
	int i = 2, m = n, root = int(sqrt(double(m)));
	for (; i <= root; i++) {
		if (m % i == 0) {
			n -= n / i;
			for (; m % i == 0; m /= i)
				;
			root = floor(sqrt(m));
		}
	}
	if (m != 1)
		n -= n / m;
	return n;
}

int gcd(int a, int b) {
	while (a != 0) {
		int c = b % a;
		b = a;
		a = c;
	}
	return b;
}

int main() {
	int vlu[100];
	int i, j, k, m, d, t, t2, ntest;
	BigInt s, p;
	cin >> ntest;
	while (ntest-- > 0) {
		cin >> m;
		s = "0";
		for (d = i = 0; i < m; d = gcd(d, vlu[i]), i++)
			cin >> vlu[i];
		for (k = i = 0; i < m; k += vlu[i], i++)
			vlu[i] /= d;
		for (i = 1; i <= d; i++)
			if (d % i == 0) {
				p = "1";
				for (t = 2; t <= k * i; t++)
					p = p * t;
				for (j = 0; j < m; j++)
					for (t = 2; t <= vlu[j] * i; t++)
						p = p.divide(t, t2);
				s = s + p * EulerPHI(d / i);
			}
		s = s.divide(k * d, t2);
		cout << s.tostring() << endl;
	}
	return 0;
}

BigInt::BigInt(const BigInt &b) {
	len = b.len;
	memset(s, 0, sizeof(s));
	for (int i = 0; i < len; i++)
		s[i] = b.s[i];
}

BigInt& BigInt::operator =(const BigInt &b) {
	len = b.len;
	memset(s, 0, sizeof(s));
	for (int i = 0; i < len; i++)
		s[i] = b.s[i];
	return *this;
}

BigInt& BigInt::operator =(const string& S) {
	int i, j, sum, t;
	string str = S;
	for (i = 0; str[i] == '0' && i < str.size() - 1; i++)
		;
	str.erase(0, i);
	memset(s, 0, sizeof(s));
	for (j = sum = 0, t = 1, i = str.size() - 1; i >= 0; i--) {
		sum += (str[i] - 48) * t;
		if (t * 10 == BASE) {
			t = 1;
			s[j++] = sum;
			sum = 0;
		} else
			t *= 10;
	}
	if (t > 1)
		s[j++] = sum;
	len = j;
	return *this;
}

string BigInt::tostring() const {
	int i, j;
	string str;
	for (i = len - 1; i >= 0; i--)
		for (j = BASE; j > 1; j /= 10)
			str += s[i] % j / (j / 10) + '0';
	for (i = 0; str[i] == '0' && i < str.size() - 1; i++)
		;
	str.erase(0, i);
	return str;
}

//高精度加法
BigInt BigInt::operator +(const BigInt &b) const {
	int i, length = len > b.len ? len : b.len;
	BigInt c(length);
	for (i = 0; i < length; i++) {
		c.s[i] += s[i] + b.s[i];
		if (c.s[i] >= BASE) {
			c.s[i] -= BASE;
			c.s[i + 1]++;
		}
	}
	if (c.s[c.len] > 0)
		c.len++;
	while (c.len > 1 && c.s[c.len - 1] == 0)
		c.len--;
	return c;
}

//高精度*单精度
BigInt BigInt::operator *(int b) const {
	BigInt c(len);
	for (int i = 0; i < c.len; i++) {
		c.s[i] += s[i] * b;
		c.s[i + 1] += c.s[i] / BASE;
		c.s[i] %= BASE;
	}
	c.len++;
	while (c.s[c.len - 1] >= BASE) {
		c.s[c.len] += c.s[c.len - 1] / BASE;
		c.s[c.len - 1] %= BASE;
		c.len++;
	}
	while (c.len > 1 && c.s[c.len - 1] == 0)
		c.len--;
	return c;
}

//高精度/单精度
BigInt BigInt::divide(const int b, int &d) const {
	int i;
	BigInt c(len);
	for (d = 0, i = len - 1; i >= 0; i--) {
		d = d * BASE + s[i];
		c.s[i] = d / b;
		d %= b;
	}
	while (c.len > 1 && c.s[c.len - 1] == 0)
		c.len--;
	return c;
}
