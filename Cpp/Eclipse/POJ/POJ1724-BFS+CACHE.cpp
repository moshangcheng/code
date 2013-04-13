/**
 * @author moshangcheng
 * @version 1.0
 * @date 2011-7-25 下午07:54:55
 * @brief POJ 1724 BFS http://poj.org/problem?id=1724
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
};

struct Node {
	int e, l, t;//t表示剩余可用的资金
	Node(int e, int l, int t) :
		e(e), l(l), t(t) {
	}
};

struct NodeCompare {
	inline bool operator ()(const Node& a, const Node& b) {
		if (a.l > b.l) {
			return true;
		} else if (a.l == b.l) {
			return a.t < b.t;
		}
		return false;
	}
};

struct PairCompare {
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

int head[MAX_N];
vector<Edge> edges;
map<pair<int, int> , int, PairCompare> nodeCache;

int main() {
	int K, N, R;
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
			edge.next = head[s];
			edges.push_back(edge);
			head[s] = edges.size() - 1;
		}
		priority_queue<Node, vector<Node> , NodeCompare> pQueue;
		pQueue.push(Node(0, 0, K));
		Node cnt(0, 0, 0);
		while (!pQueue.empty()) {
			cnt = pQueue.top();
			if (cnt.e == N - 1) {
				break;
			}
			pQueue.pop();
			nodeCache[make_pair(cnt.e, cnt.t)] = 1;
			for (int i = head[cnt.e]; i >= 0; i = edges[i].next) {
				if (edges[i].t <= cnt.t) {
					Node node(edges[i].d, cnt.l + edges[i].l, cnt.t - edges[i].t);
					if (nodeCache.find(make_pair(node.e, node.t)) == nodeCache.end()) {
						pQueue.push(node);
					}
				}
			}
		}
		if (pQueue.empty()) {
			printf("%d\n", -1);
		} else {
			printf("%d\n", cnt.l);
		}
	}
	return 0;
}
