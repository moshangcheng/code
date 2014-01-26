/**
 * @author moshangcheng
 * @version 1.0
 * @date 2011-3-25 下午06:49:28
 * @brief http://acm.hdu.edu.cn/showproblem.php?pid=1878
 */
#include <cstdio>
using namespace std;

int n, m;
//parent[i]表示第i个节点的父节点。若parent[i]小于0，则此节点为根节点，绝对值为以此节点的为根节点的树的节点数量
int parent[1001];
int degree[1001];

//find()查找节点所在树的根节点。
//因为只需要连通性，树的具体结构无关紧要，所以find()查找的同时对树进行优化，减少树的高度
int find(int i) {
	if (parent[i] > 0)
		return (parent[i] = find(parent[i]));
	else
		return i;
}

//合并两棵树，将较小的树作为较大的树的子树
void join(int i, int j) {
	if (parent[i] < parent[j]) {
		parent[i] += parent[j];
		parent[j] = i;
	} else {
		parent[j] += parent[i];
		parent[i] = j;
	}
}

int judge() {
	int i, sum = 0;
	for (i = 1; i <= n; i++) {
		if (parent[i] < 0)
			sum++;
	}
	if (sum > 1)
		return 0;
	for (i = 1; i <= n; i++) {
		if (degree[i] % 2 != 0)
			return 0;
	}
	return 1;
}

int main() {
	int i, start, end;
	while (scanf("%d", &n) == 1 && n != 0) {
		for (i = 0; i < 1001; i++) {
			parent[i] = -1;
			degree[i] = 0;
		}

		scanf("%d", &m);
		for (i = 0; i < m; i++) {
			scanf("%d%d", &start, &end);
			//两棵树有边联通，那么合并这两棵树
			int root1 = find(start);
			int root2 = find(end);
			if (root1 != root2) {
				join(root1, root2);
			}
			degree[start]++;
			degree[end]++;
		}
		printf("%d\n", judge());
	}
	return 0;
}

