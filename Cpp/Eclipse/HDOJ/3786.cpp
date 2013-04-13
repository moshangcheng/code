/**
 * @author moshangcheng
 * @version 1.0
 * @date 2011-3-25 下午06:49:28
 * @brief http://acm.hdu.edu.cn/showproblem.php?pid=3786
 */
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <vector>
using namespace std;

int dist[26][26];
int parent[26][2];

const int MAX = 1000000;

void init() {
	for (int i = 0; i < 26; i++) {
		parent[i][0] = parent[i][1] = -1;
		for (int j = 0; j < 26; j++) {
			dist[i][j] = -1;
		}
	}
}

int minDepth;
void isParent(int test, int child, int depth) {
	if (child == test && depth < minDepth && depth != 0) {
		minDepth = depth;
	}
	if (parent[child][0] >= 0) {
		isParent(test, parent[child][0], depth + 1);
	}
	if (parent[child][1] >= 0) {
		isParent(test, parent[child][1], depth + 1);
	}
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
				parent[charA - 'A'][0] = charB - 'A';
			}
			if (charC != '-') {
				parent[charA - 'A'][1] = charC - 'A';
			}
		}
		for (int i = 0; i < m; i++) {
			bool flag = 1;
			char A, B;
			minDepth = MAX;
			cin >> A >> B;
			isParent(A-'A', B-'A', 0);
			if(minDepth == MAX) {
				flag = 0;
			}
			isParent(B-'A', A-'A', 0);
			if(minDepth == MAX) {
				printf("-\n");
			}
			else {
				for(int i = 2; i < minDepth; i++) {
					printf("great-");
				}
				if(minDepth > 1) {
					printf("grand");
				}
				if(flag) {
					printf("parent\n");
				}
				else {
					printf("child\n");
				}
			}
		}
	}
}
