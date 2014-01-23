//在线等价类问题
//所谓在线等价类问题，就是必须不断的进行不同等价类之间的合并
//而离线等价类问题，则只是在已知各个元素之间关系的前提下划分等价类
#include <iostream>
using namespace std;

//利用重量规则进行合并，非根节点的parent域保存其根节点值，而根节点
//的parent域保存其子树节点的数量。
int* parent;
bool* root;

void Initialize(int n) {
	root = new bool[n + 1];
	parent = new int[n + 1];
	for (int e = 1; e <= n; e++) {
		parent[e] = 1;
		root[e] = true;
	}
}

int Find(int e) {
	while (!root[e])
		e = parent[e];
	return e;
}

void Union(int i, int j) {
	if (parent[i] < parent[j]) {
		parent[j] += parent[i];
		root[i] = false;
		parent[i] = j;
	} else {
		parent[i] += parent[j];
		root[j] = false;
		parent[j] = i;
	}
}

int main() {
	return 0;
}

