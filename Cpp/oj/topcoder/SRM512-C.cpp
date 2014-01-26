/**
 * @author moshangcheng
 * @version 1.0
 * @date 2011-7-20 下午01:41:41
 * @brief 本题考虑二分图最大匹配算法，但是贪婪算法也可以解决问题
 */
#include <vector>
#include <list>
#include <map>
#include <set>
#include <queue>
#include <deque>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;

class DoubleRoshambo {
public:
	int compare[26][26];

	void init() {
		fill(compare[0], compare[26], 0);
		compare['P' - 'A']['R' - 'A'] = 1;
		compare['R' - 'A']['P' - 'A'] = -1;
		compare['P' - 'A']['S' - 'A'] = -1;
		compare['S' - 'A']['P' - 'A'] = 1;
		compare['R' - 'A']['S' - 'A'] = 1;
		compare['S' - 'A']['R' - 'A'] = -1;
	}

	inline int getScore(string a, string e) {
		int rightCompare = compare[a[1] - 'A'][e[1] - 'A'];
		int leftCompare = compare[a[0] - 'A'][e[0] - 'A'];
		if (rightCompare == 1) {
			if (leftCompare == 1) {
				return 2;
			} else if (leftCompare == 0) {
				return 1;
			}
		}
		return 0;
	}
	int maxScore(vector<string> A, vector<string> E) {
		init();
		list<string> a(A.begin(), A.end()), e(E.begin(), E.end());
		int flag, sum = 0;
		list<string>::iterator i, j;
		for (i = a.begin(); i != a.end();) {
			flag = 0;
			for (j = e.begin(); j != e.end(); j++) {
				if (getScore(*i, *j) == 2) {
					flag = 1;
					i = a.erase(i);
					j = e.erase(j);
					sum += 2;
					break;
				}
			}
			if (!flag) {
				i++;
			}
		}
		for (i = a.begin(); i != a.end();) {
			flag = 0;
			for (j = e.begin(); j != e.end(); j++) {
				if (getScore(*i, *j) == 1) {
					flag = 1;
					i = a.erase(i);
					j = e.erase(j);
					sum += 1;
					break;
				}
			}
			if (!flag) {
				i++;
			}
		}
		return sum;
	}
};
