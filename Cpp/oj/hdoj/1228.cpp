/**
 * @author moshangcheng
 * @version 1.0
 * @date 2011-3-25 下午06:49:28
 * @brief http://acm.hdu.edu.cn/showproblem.php?pid=1228
 */
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

const string s[10] = { "zero", "one", "two", "three", "four", "five", "six",
		"seven", "eight", "nine" };

int find(const string str) {
	int i;
	for (i = 0; i < 10; i++)
		if (str == s[i])
			break;
	return i;
}

int main() {
	int a, b;
	string in_str, s;
	istringstream in_str_stream;
	while (getline(cin, in_str, '\n')) {
		a = b = 0;
		in_str_stream.clear();
		in_str_stream.str(in_str);
		while (in_str_stream >> s) {
			if (s == "+")
				break;
			a = a * 10 + find(s);
		}
		while (in_str_stream >> s) {
			if (s == "=")
				break;
			b = b * 10 + find(s);
		}
		if (a == 0 && b == 0)
			break;
		cout << a + b << endl;
	}
	return 0;
}
