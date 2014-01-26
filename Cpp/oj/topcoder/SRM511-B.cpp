/**
 * @author moshangcheng
 * @version 1.0
 * @date 2011-7-20 下午01:43:27
 * @brief
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

class Zoo {
public:
	long long theCount(vector<int> answers) {
		sort(answers.begin(), answers.end());
		int minLength = 0, cntLength = 0;
		for (int i = 0; i < answers.size(); i++, cntLength++) {
			if (answers[i] != cntLength) {
				return 0;
			}
			if (i < answers.size() - 1 && answers[i + 1] == cntLength) {
				if (minLength == cntLength) {
					minLength++;
					i++;
					continue;
				} else {
					return 0;
				}
			}
		}
		long long num = 1;
		for (int i = 0; i < minLength; i++) {
			num *= 2;
		}
		if (minLength < cntLength) {
			num *= 2;
		}
		return num;
	}
};
