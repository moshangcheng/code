/**
 * @author moshangcheng
 * @version 1.0
 * @date 2011-7-25 下午07:54:55
 * @brief POJ 1724 DFS DP http://poj.org/problem?id=1724
 */

#include <iostream>
#include <cstdio>
#include <cmath>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>
#include <utility>
using namespace std;

struct Edge {
	int d, l, t;
	int next;
	bool visited;//数据是有环的，所以必须判断边是否访问过
};

struct MapCompare {
	inline bool operator ()(const pair<int, int>& a, const pair<int, int>& b) {
		if (a.first < b.first) {
			return true;
		} else if (a.first == b.first && a.second < b.second) {
			return true;
		}
		return false;
	}
};

const int MAX_N = 100;
const int IMPOSSIBLE = 99999999;

int K, N, R;
int head[MAX_N];
vector<Edge> edges;
map<pair<int, int> , int, MapCompare> nodeCache;

int solve(int s, int k, int v) {
	if (v < 0) {
		return IMPOSSIBLE;
	}
	if (s == N - 1) {
		return 0;
	}
	map<pair<int, int>, int>::iterator cnt = nodeCache.find(make_pair(s, k));
	if (cnt != nodeCache.end()) {
		//必须判断返回值是否满足剪枝条件，否则会导致上层搜索判断出错
		return (cnt->second <= v ? cnt->second : IMPOSSIBLE);
	}
	int min = IMPOSSIBLE;
	for (int i = head[s]; i >= 0; i = edges[i].next) {
		if (!edges[i].visited && edges[i].t <= k) {
			//开启剪枝
			int limit = (min < v ? min : v);
			limit = (limit == IMPOSSIBLE ? IMPOSSIBLE : limit - edges[i].l);
			edges[i].visited = true;
			int value = solve(edges[i].d, k - edges[i].t, limit);
			edges[i].visited = false;
			if (value != IMPOSSIBLE && value + edges[i].l < min) {
				min = value + edges[i].l;
			}
		}
	}
	if(v <= min && min < IMPOSSIBLE) {
		cnt->second = min;
	}
	return min;
}

int main() {
	while (scanf("%d%d%d", &K, &N, &R) == 3) {
		edges.clear();
		edges.reserve(R);
		nodeCache.clear();
		fill(head, head + MAX_N, -1);
		for (int i = 0; i < R; i++) {
			int s;
			Edge edge;
			scanf("%d%d%d%d", &s, &edge.d, &edge.l, &edge.t);
			s--;
			edge.d--;
			edge.visited = false;
			edge.next = head[s];
			edges.push_back(edge);
			head[s] = edges.size() - 1;
		}
		int ans = solve(0, K, IMPOSSIBLE);
		printf("%d\n", (ans == IMPOSSIBLE ? -1 : ans));
	}
	return 0;
}
