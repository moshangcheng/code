/**
 * @author moshangcheng
 * @version 1.0
 * @date 2011-7-22 下午04:56:04
 * @brief TopCoder SRM509 B
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

class LuckyRemainder {
public:
	int getLuckyRemainder(string X) {
		int power[100];
		power[0] = 1;
		for (int i = 1; i <= X.size(); i++) {
			power[i] = (power[i - 1] * 2) % 9;
		}
		int sumNumSum = 0;
		for (int i = 0; i < X.size(); i++) {
			sumNumSum = ((X[i] - '0') * power[i] + sumNumSum * 11) % 9;
		}
		return sumNumSum;
	}
};
