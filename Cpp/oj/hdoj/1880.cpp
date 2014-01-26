/**
 * @author moshangcheng
 * @version 1.0
 * @date 2011-3-25 下午06:49:28
 * @brief http://acm.hdu.edu.cn/showproblem.php?pid=1880
 */
#include <iostream>
#include <map>
#include <string>
using namespace std;

int main() {
	int i, N;
	char tmp;
	string mozhou, fct;
	map<string, string> dict1, dict2;
	while (cin.get(tmp)) {
		if (tmp == '[') {
			getline(cin, mozhou, ']');
			cin.get(tmp);
			getline(cin, fct, '\n');
			dict1[mozhou] = fct;
			dict2[fct] = mozhou;
		} else {
			getline(cin, mozhou, '\n');
			break;
		}
	}
	cin >> N;
	cin.get(tmp);
	for (i = 0; i < N; i++) {
		getline(cin, mozhou, '\n');
		if (mozhou[0] == '[') {
			mozhou = mozhou.substr(1, mozhou.size() - 2);
			fct = dict1[mozhou];
			if (fct == "")
				cout << "what?\n";
			else
				cout << fct << endl;
		} else {
			fct = mozhou;
			mozhou = dict2[fct];
			if (mozhou == "")
				cout << "what?\n";
			else
				cout << mozhou << endl;
		}
	}
	return 0;
}
