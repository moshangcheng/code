/**
 * @author moshangcheng
 * @version 1.0
 * @date 2011-3-25 下午02:50:15
 * @brief http://acm.zju.edu.cn/onlinejudge/showProblem.do?problemCode=1014
 */
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

string expression;
int d[1000], start, end, pos[1000], m;

void op(int k) //每次取子表达式通过改变start,end的值来实现
{
	if (k > m)
		return;
	int num = 0, i, sign = -1, p = 0;//sign表示当前运算符，0为'+',1为'*',2为'^'，p为运算符的个数
	for (i = start; i <= end; i++) {
		if (expression[i] == '(')
			num++;
		else if (expression[i] == ')')
			num--;
		else if (expression[i] >= 'a' && expression[i] <= 'z')
			continue;
		else if (num > 0)
			continue;
		else //只有括号对称的操作符才进行计算
		{
			if (expression[i] == '+') {
				if (sign != 0)
					sign = 0, p = 0, pos[p] = i, p++;
				else
					pos[p] = i, p++;
			} else if (expression[i] == '*') {
				if (sign == 0)
					continue;
				else if (sign == -1 || sign == 2)
					sign = 1, p = 0, pos[p] = i, p++;
				else
					pos[p] = i, p++;
			} else {
				if (sign == 0 || sign == 1)
					continue;
				else if (sign == -1)
					sign = 2, p = 0, pos[p] = i, p++;
				else
					pos[p] = i, p++;

			}
		}
	}
	//子表达式的个数为p+1
	if (p == 0) //只有一个子表达式
	{
		if (expression[start] == '(' && expression[end] == ')')
			start++, end--;
	} else {
		if (d[k - 1] == 1) {
			end = pos[0] - 1;
		} else if (d[k - 1] == p + 1) {
			start = pos[p - 1] + 1;
		} else {
			start = pos[d[k - 1] - 2] + 1, end = pos[d[k - 1] - 1] - 1;
		}
	}
	op(k + 1);
}
int main() {
	// ifstream cin("in.txt");
	string s;
	int n, k, caseNum = 0, i;
	while (cin >> expression) {
		if (expression.length() == 1 && expression[0] == '*')
			break;
		caseNum++;
		if (caseNum > 1)
			cout << endl;
		cout << "Expression " << expression[0] << ":" << endl;
		cin >> n;
		cin.ignore();
		while (n--) {
			getline(cin, s);
			istringstream in(s);
			m = 0;
			while (in >> k) {
				d[m] = k;
				m++;
			}
			start = 3;
			end = expression.length() - 1;
			op(1);
			for (i = m - 1; i >= 0; i--)
				cout << "op(" << d[i] << ",";
			cout << expression[0];
			for (i = 1; i <= m; i++)
				cout << ')';
			cout << '=';
			for (i = start; i <= end; i++)
				cout << expression[i];
			cout << endl;
		}
	}
	return 0;
}
