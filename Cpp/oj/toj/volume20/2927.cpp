//假设起点高度和h1小于终点h2，h1<h2，
//那么高度在h1和h2之间的点高度差可认为是0，
//高度大于h2的点,高度差为h-h2;高度小于h1的点，高度差为h-h1;
//将所有点按其与起点和终点的高度差排序。
//首先将起点和终点放入集合s中，然后按高度差从小到大的顺序依次添加点，
//当然高度差相同的点须一起加入，
//判断集合s的连通性，一旦连通，就用dijkstra算法寻找最短路径。
//此时求出的最短路径就是所求路径。

//假设起点为1，终点为5
//i     1    2    3    4    5
//高度  50   40   70   90   60
//假设从点1到点5只有唯一一条通路1-3-4-5，那么高度差为 40
//但按照此算法，点的添加次序是：
//1和5为初始化后的点集合，然后将2和3一起加入集合，此时没有通路，最后添加点4，
//发现通路，由此得出的高度差为 50

//当判断集合是否连通时，必须采用标程的方法。若用如下方法，则是错误的
//先把起点赋值为0，终点赋值为n-1，此时有两个连通分支：起点和终点
//然后从按高度排序的点i到点j
//若i与值为0的分支连通，则将其添加到 此分支中
//若其与值为n-1的分支连通，则将其添加到此分支中
//若 与两个分支都连通，则集合连通
//这个方法是错误的，反例如下：
//i  0   1   2   3   4
//h  5   6   3   7   8
//点0与1连通，点3与4连通，点2与1和2连通
//按算法，先取点2，其与0和4都不连通，导致其不会添加到任意分支中去
//而实际上，其余任一分支都连通
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

int prt[100];
const int MAX = 1000000000;
struct CROSS {
	int h, i;
};
struct NEIBR {
	int i, d;
};

bool operator <(CROSS a, CROSS b) {
	return a.h < b.h;
}

int root(int p) {
	if (prt[p] == p)
		return p;
	return prt[p] = root(prt[p]);
}

void joint(int a, int b) {
	int s1 = root(a);
	int s2 = root(b);
	if (s1 != s2)
		prt[s1] = s2;
}

int main() {
	CROSS height[100];
	vector<NEIBR> p[100];
	int t, n, m, besth, od, minh, maxh;
	int num[2], d[100], vst[100], t_vst[100];

	scanf("%d", &t);
	while (t-- > 0) {
		scanf("%d%d", &n, &m);
		for (int i = 0; i < n; i++) {
			scanf("%d", &height[i].h);
			height[i].i = i;
			p[i].clear();
		}
		for (int j = 0; j < m; j++) {
			NEIBR x;
			int r, s, dist;
			scanf("%d%d%d", &r, &s, &dist);
			r--;
			s--;
			x.i = r;
			x.d = dist;
			p[s].push_back(x);
			x.i = s;
			p[r].push_back(x);
		}
		if (n == 1) {
			printf("0 0\n");
			continue;
		}
		sort(height, height + n);
		for (int i = 0, j = 0; i < n; i++)
			if (height[i].i == 0 || height[i].i == (n - 1))
				num[j++] = i;

		besth = MAX;
		for (int i = num[0]; i >= 0; i--) {
			if (i != 0 && height[i].h == height[i - 1].h)
				continue;
			minh = height[i].h;
			maxh = height[num[1]].h;
			memset(vst, 0, sizeof(vst));
			for (int j = 0; j < n; j++)
				prt[j] = j;
			for (int j = i; j < n; j++) {
				od = height[j].i;
				vst[od] = 1;
				if (maxh < height[j].h)
					maxh = height[j].h;
				if (maxh - height[i].h > besth)
					break;
				for (int k = 0; k < p[od].size(); k++)
					if (vst[p[od][k].i] == 1)
						joint(od, p[od][k].i);
				if (j < n - 1 && height[j].h == height[j + 1].h)
					continue;
				if (root(0) == root(n - 1)) {
					memcpy(t_vst, vst, sizeof(vst));
					besth = maxh - minh;
					break;
				}
			}
		}
		int mind, minp;
		memset(d, 0x3f, sizeof(d));
		d[0] = 0;
		while (1) {
			mind = MAX;
			minp = -1;
			for (int k = 0; k < n; k++)
				if (t_vst[k] > 0 && d[k] < mind) {
					mind = d[k];
					minp = k;
				}
			if (minp == n - 1 || minp == -1)
				break;
			t_vst[minp] = -t_vst[minp];
for		(int k = 0; k < p[minp].size(); k++ )
		d[ p[minp][k].i ] <?= mind + p[minp][k].d;
	}
	printf("%d %d\n", besth, d[n-1]);
}
return 0;
}

