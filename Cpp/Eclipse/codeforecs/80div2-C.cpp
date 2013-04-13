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

const int MAX = 100;

int v, e;
bool visited[MAX];
bool matrix[MAX][MAX];

void solve(int node) {
	visited[node] = true;
	for(int i = 0; i < v; i++) {
		if(!visited[i] && matrix[node][i]) {
			solve(i);
		}
	}
}

int main() {
	while (cin >> v >> e) {
		fill(visited, visited + MAX, false);
		fill(matrix[0], matrix[MAX], false);
		int start, end;
		for (int i = 0; i < e; i++) {
			cin >> start >> end;
			start--;
			end--;
			matrix[start][end] = matrix[end][start] = true;
		}
		solve(0);
		int unvisited = 0;
		for(int i = 0; i < v; i++) {
			if(!visited[i]) {
				unvisited++;
			}
		}
		if(v == e && unvisited == 0) {
			cout << "FHTAGN!\n";
		} else {
			cout << "NO\n";
		}
	}
}
