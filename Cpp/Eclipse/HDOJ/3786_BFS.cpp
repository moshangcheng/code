/**
 * @author moshangcheng
 * @version 1.0
 * @date 2011-3-25 下午06:49:28
 * @brief http://acm.hdu.edu.cn/showproblem.php?pid=3786
 */
#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;

vector<int> parent[26];

const int MAX = 1000000;

void init() {
	for (int i = 0; i < 26; i++) {
		parent[i].clear();
	}
}

int BFS(int test, int child) {
	if (test == child) {
		return 0;
	}
	int depth = MAX;
	vector<int> current;
	vector<int> next;
	current.push_back(child);
	for (depth = 0; !current.empty(); depth++) {
		for (int i = 0; i < current.size(); i++) {
			if (current[i] == test) {
				return depth;
			}
		}

		next.clear();
		for (int i = 0; i < current.size(); i++) {
			next.insert(next.end(), parent[current[i]].begin(),
					parent[current[i]].end());
		}
		swap(current, next);
	}
	return MAX;
}

int main() {
	int n, m;
	char charA, charB, charC;
	while (cin >> n >> m) {
		if (n == 0 && m == 0)
			break;
		init();
		for (int i = 0; i < n; i++) {
			cin >> charA >> charB >> charC;
			if (charB != '-') {
				parent[charA - 'A'].push_back(charB - 'A');
			}
			if (charC != '-') {
				parent[charA - 'A'].push_back(charC - 'A');
			}
		}
		for (int i = 0; i < m; i++) {
			bool flag = 1;
			int depth;
			char A, B;
			cin >> A >> B;
			depth = BFS(A - 'A', B - 'A');
			if (depth == MAX) {
				flag = 0;
				depth = BFS(B - 'A', A - 'A');
			}
			if (depth == MAX || depth == 0) {
				printf("-\n");
			} else {
				for (int i = 2; i < depth; i++) {
					printf("great-");
				}
				if (depth > 1) {
					printf("grand");
				}
				if (flag) {
					printf("parent\n");
				} else {
					printf("child\n");
				}
			}
		}
	}
}
