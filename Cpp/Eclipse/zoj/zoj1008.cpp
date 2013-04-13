/**
 * @author moshangcheng
 * @version 1.0
 * @date 2011-3-25 下午03:27:24
 * @brief http://acm.zju.edu.cn/onlinejudge/showProblem.do?problemCode=1010
 */
#include <vector>
#include <cstdio>
#include <iostream>
using namespace std;

int m, n;
int value[25];
int squares[25][5];
vector<int> adjData[26][26];

bool search(int Depth);
void init();
void cclData();

int main() {
	for (int number = 1; scanf("%d", &n) == 1; number++) {
		if (n == 0) {
			break;
		}

		m = 0;
		for (int i = 0; i < n * n; i++, m++) {
			for (int k = 0; k < 4; k++) {
				scanf("%d", &(squares[m][k]));
			}
			squares[m][4] = 1;
			for (int j = 0; j < m; j++) {
				if (squares[m][0] == squares[j][0] && squares[m][1]
						== squares[j][1] && squares[m][2] == squares[j][2]
						&& squares[m][3] == squares[j][3]) {
					m--;
					squares[j][4]++;
					break;
				}
			}
		}

		init();
		cclData();
		if (number > 1)
			printf("\n");
		printf("Game %d: %s\n", number, search(0) ? "Possible" : "Impossible");
	}
}

bool search(int Depth) {
	if (Depth == n * n) {
		return true;
	}
	int indexTop, indexLeft;
	if (Depth / n == 0)
		indexTop = m;
	else
		indexTop = value[Depth - n];
	if (Depth % n == 0)
		indexLeft = m;
	else
		indexLeft = value[Depth - 1];
	for (int k = 0; k < adjData[indexTop][indexLeft].size(); k++) {
		int index = adjData[indexTop][indexLeft][k];
		if (squares[index][4] == 0) {
			continue;
		}
		value[Depth] = index;
		squares[index][4]--;
		if (search(Depth + 1)) {
			squares[index][4]++;
			return true;
		}
		squares[index][4]++;
	}
	return false;
}

void cclData() {
	for (int i = 0; i < m; i++)
		for (int j = 0; j < m; j++)
			for (int k = 0; k < m; k++)
				if (squares[i][2] == squares[k][0] && squares[j][1]
						== squares[k][3]) {
					adjData[i][j].push_back(k);
				}

	for (int j = 0; j < m; j++)
		for (int k = 0; k < m; k++)
			if (squares[j][1] == squares[k][3]) {
				adjData[m][j].push_back(k);
			}

	for (int i = 0; i < m; i++)
		for (int k = 0; k < m; k++)
			if (squares[i][2] == squares[k][0]) {
				adjData[i][m].push_back(k);
			}

	for (int k = 0; k < m; k++) {
		adjData[m][m].push_back(k);
	}
}

void init() {
	for (int i = 0; i < 26; i++)
		for (int j = 0; j < 26; j++) {
			adjData[i][j].clear();
		}
}

