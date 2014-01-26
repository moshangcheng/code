/**
 * @author moshangcheng
 * @version 1.0
 * @date 2011-7-20 下午01:44:22
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

class TheAlmostLuckyNumbersDivTwo {
public:
	int find(int a, int b) {
		int luckySum = 0;
		for (int i = a; i <= b; i++) {
			int value = i, unluckySum = 0;
			for (; value > 0; value /= 10) {
				if (value % 10 != 4 && value % 10 != 7) {
					unluckySum++;
				}
			}
			if (unluckySum <= 1) {
				luckySum++;
			}
		}
		return luckySum;
	}
};

