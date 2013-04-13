/**
 * @author moshangcheng
 * @version 1.0
 * @date 2011-7-20 下午01:43:48
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

class GameOfLifeDivTwo {
public:
	char inline getState(int v) {
		if (v >= 2) {
			return '1';
		} else {
			return '0';
		}
	}
	string theSimulation(string init, int T) {
		int length = init.size();
		string prevString, cntString = init;
		for (int i = 0; i < T; i++) {
			prevString = cntString;
			cntString[0] = getState(prevString[0] + prevString[length - 1]
					+ prevString[1] - '0' * 3);
			for (int j = 1; j < length - 1; j++) {
				cntString[j] = getState(prevString[j] + prevString[j - 1]
						+ prevString[j + 1] - '0' * 3);
			}
			cntString[length - 1] = getState(prevString[0] + prevString[length
					- 1] + prevString[length - 2] - '0' * 3);
		}
		return cntString;
	}
};

