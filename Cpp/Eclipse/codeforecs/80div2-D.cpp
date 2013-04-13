/**
 * @author moshangcheng
 * @version 1.0
 * @date 2011-8-7 下午06:58:33
 * @brief cf 80 div2
 */
#include <iostream>
#include <cstdio>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;

const long long MAX = 1000;

char ans[MAX];
long long query[MAX];

int main() {
	long long n, k, p;
	while (cin >> n >> k >> p) {
		for (long long i = 0; i < p; i++) {
			cin >> query[i];
			query[i]--;
		}
		if (2 * k < n) {
			if (n % 2 == 0 || k == 1) {
				for (long long i = 0; i < p; i++) {
					if (query[i] < n - 2 * k || query[i] % 2 == n % 2) {
						cout << ".";
					} else {
						cout << "X";
					}
				}
			} else {
				for (long long i = 0; i < p; i++) {
					if (query[i] < n - 2 * k + 2) {
						cout << ".";
					} else if (query[i] >= n - 2 * k + 4 && query[i] % 2 == n
							% 2) {
						cout << ".";
					} else {
						cout << "X";
					}
				}
			}
		} else {
			for (long long i = 0; i < p; i++) {
				if (query[i] < 2 * (n - k) && query[i] % 2 == 0) {
					cout << ".";
				} else {
					cout << "X";
				}
			}
		}
		cout << endl;
	}
}
