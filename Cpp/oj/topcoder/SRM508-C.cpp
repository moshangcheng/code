﻿/**
 * @author moshangcheng
 * @version 1.0
 * @date 2011-7-26 下午01:19:22
 * @brief TopCoder SRM508 C DP DFS Cache
 * 	如果没有每个数必须不能大于R的限制，即S[N][K]表示满足 (+Ai) = (|Ai) = K的序列个数
 * 那么S[N]= N^m，m为K的二进制表示中1的个数
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

const int MAX_N = 11;
const int MAX_S = 16384;//1 << (int(ceil(log2(15000.0))));
const int MOD = 1000000009;
int S[MAX_N][MAX_S];
vector<int> childs[MAX_S];

class YetAnotherORProblem2 {
public:
	int N, R, L;
	int solve(int n, int s) {
		if(S[n][s] >= 0) {
			return S[n][s];
		}
		if (n == 1) {
			return (S[n][s] = (s <= R));
		}
		//没有缓存
		if (childs[s].empty()) {
			int v = s, numOfOnes = 0, childNums;
			int digits[40];
			for (int i = 0; v > 0; v /= 2, i++) {
				if (v % 2 == 1) {
					digits[numOfOnes++] = 1 << i;
				}
			}
			childNums = 1 << numOfOnes;
			for (int i = 0; i < childNums; i++) {
				int child = 0;
				for (int j = 0, v = i; v > 0; j++, v /= 2) {
					if (v % 2 == 1) {
						child += digits[j];
					}
				}
				childs[s].push_back(child);
			}
		}
		int sum = 0;
		for (int i = 0; i < childs[s].size(); i++) {
			if (childs[s][i] <= R) {
				sum = (sum + solve(n - 1, s - childs[s][i])) % MOD;
			}
		}
		return (S[n][s] = sum);
	}

	int countSequences(int N, int R) {
		this->N = N;
		this->R = R;
		this->L = 1 << (int(ceil(log2(1.0 * R + 0.5))));
		int sum = 0;
		fill(S[0], S[MAX_N], -1);
		for (int i = 0; i < L; i++) {
			sum = (sum + solve(N, i)) % MOD;
		}
		return sum;
	}
};

// BEGIN KAWIGIEDIT TESTING
// Generated by KawigiEdit 2.1.4 (beta) modified by pivanof
bool KawigiEdit_RunTest(int testNum, int p0, int p1, bool hasAnswer, int p2) {
	cout << "Test " << testNum << ": [" << p0 << "," << p1;
	cout << "]" << endl;
	YetAnotherORProblem2 *obj;
	int answer;
	obj = new YetAnotherORProblem2();
	clock_t startTime = clock();
	answer = obj->countSequences(p0, p1);
	clock_t endTime = clock();
	delete obj;
	bool res;
	res = true;
	cout << "Time: " << double(endTime - startTime) / CLOCKS_PER_SEC << " seconds" << endl;
	if (hasAnswer) {
		cout << "Desired answer:" << endl;
		cout << "\t" << p2 << endl;
	}
	cout << "Your answer:" << endl;
	cout << "\t" << answer << endl;
	if (hasAnswer) {
		res = answer == p2;
	}
	if (!res) {
		cout << "DOESN'T MATCH!!!!" << endl;
	} else if (double(endTime - startTime) / CLOCKS_PER_SEC >= 2) {
		cout << "FAIL the timeout" << endl;
		res = false;
	} else if (hasAnswer) {
		cout << "Match :-)" << endl;
	} else {
		cout << "OK, but is it right?" << endl;
	}
	cout << "" << endl;
	return res;
}
int main() {
	bool all_right;
	all_right = true;

	int p0;
	int p1;
	int p2;

	{
	// ----- test 0 -----
	p0 = 2;
	p1 = 2;
	p2 = 7;
	all_right = KawigiEdit_RunTest(0, p0, p1, true, p2) && all_right;
	// ------------------
	}

	{
	// ----- test 1 -----
	p0 = 2;
	p1 = 3;
	p2 = 9;
	all_right = KawigiEdit_RunTest(1, p0, p1, true, p2) && all_right;
	// ------------------
	}

	{
	// ----- test 2 -----
	p0 = 3;
	p1 = 3;
	p2 = 16;
	all_right = KawigiEdit_RunTest(2, p0, p1, true, p2) && all_right;
	// ------------------
	}

	{
	// ----- test 3 -----
	p0 = 7;
	p1 = 1023;
	p2 = 73741815;
	all_right = KawigiEdit_RunTest(3, p0, p1, true, p2) && all_right;
	// ------------------
	}

	{
	// ----- test 4 -----
	p0 = 2;
	p1 = 8191;
	p2 = 1594323;
	all_right = KawigiEdit_RunTest(4, p0, p1, true, p2) && all_right;
	// ------------------
	}

	{
	// ----- test 5 -----
	p0 = 3;
	p1 = 4235;
	p2 = 30295792;
	all_right = KawigiEdit_RunTest(5, p0, p1, true, p2) && all_right;
	// ------------------
	}

	if (all_right) {
		cout << "You're a stud (at least on the example cases)!" << endl;
	} else {
		cout << "Some of the test cases had errors." << endl;
	}
	return 0;
}
// END KAWIGIEDIT TESTING