/**
 * @author moshangcheng
 * @version 1.0
 * @date 2011-3-25 下午06:49:28
 * @brief http://acm.hdu.edu.cn/showproblem.php?pid=1233
 */
#include <cstdio>
#include <queue>
using namespace std;

#define Maxv 100+5

typedef struct {
	int v1, v2, len;
} Node;

bool operator >(Node a, Node b) {
	if (a.len > b.len)
		return true;
	return false;
}

int fa[Maxv];

int Getfa(int i) {
	if (fa[i] == i)
		return i;
	fa[i] = Getfa(fa[i]);
	return fa[i];
}

int main() {
	int n, sum;
	priority_queue<Node, vector<Node> , greater<Node> > Q; //

	int i, j, len;
	Node e;
	while (scanf("%d", &n) && n) {
		int m = n * (n - 1) / 2;
		while (!Q.empty())
			Q.pop();
		while (m--) {
			scanf("%d%d%d", &i, &j, &len);
			e.v1 = i, e.v2 = j, e.len = len;
			Q.push(e); //
		}
		for (i = 1; i <= n; i++)
			fa[i] = i; //

		sum = 0;
		while (Q.size() != 0) {
			Node e;
			e = Q.top(); //
			Q.pop();
			if (Getfa(e.v1) != Getfa(e.v2)) //
			{
				sum += e.len;
				fa[Getfa(e.v2)] = Getfa(e.v1);
			}
		}
		printf("%d\n", sum);
	}
	return 0;
}
