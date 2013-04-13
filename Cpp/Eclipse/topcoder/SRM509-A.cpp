/**
 * @author moshangcheng
 * @version 1.0
 * @date 2011-7-22 下午04:34:15
 * @brief TopCoder SRM 509 A
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

const int MAX = 100001;
vector<int> palindromicNum;

class PalindromizationDiv2 {
public:
	bool ispalindromic(int x) {
		if (x == 0) {
			return true;
		}
		int len;
		int digits[10];
		for (len = 0; x > 0; len++, x /= 10) {
			digits[len] = x % 10;
		}
		for (int i = 0, j = len - 1; i <= j; i++, j--) {
			if (digits[i] != digits[j]) {
				return false;
			}
		}
		return true;
	}
	int getMinimumCost(int X) {
		if (ispalindromic(X)) {
			return 0;
		}
		for (int len = 1,  i = X - 1, j = X + 1;; i--, j++, len++) {
			if(ispalindromic(i) || ispalindromic(j)) {
				return len;
			}
		}
	}
};

