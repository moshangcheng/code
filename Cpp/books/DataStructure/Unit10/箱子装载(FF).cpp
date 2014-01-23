//箱子装载问题是NP-复杂问题，它的近似解法有四种:
//1) 最先匹配法(First Fit,FF)
//2) 最优先匹配法(Best Fit,BF)
//3) 最先匹配递减法(First Fit Decreaing,FFD)
//4) 最优匹配递减法(Best Fit Decreaing, BFD)

#include <iostream>
#include "WinnerTree.h"
using namespace std;

template<class T>
int winner(T*a, int b, int c) {
	if (a[b] < a[c])
		return c;
	else
		return b;
}

int FirstFitPack(int*s, int n, int c) {//n为物品数量，s[]为各物品所需要的空间
	WinnerTree<int>* W = new WinnerTree<int> (n);
	int*avail = new int[n + 1];

	for (int i = 1; i <= n; i++)
		avail[i] = c;//初始化
	W->Initialize(avail, n, winner);//因为最多需要n个箱子
	for (int i = 1; i <= n; i++) {
		int p = 2;
		while (p < n) {//p是外部节点时,循环结束
			int winp = W->Winner(p);//Winner(p)是内部节点p处的比赛的胜者
			if (avail[winp] < s[i])
				p++;
			//第一个箱子在右子树中
			//此处p自增后 ,有可能为外部节点,即p=n,n为奇数，n-1为偶数
			//若p为内部节点,t[p]显然能装下物品，但t[p]若是p的右节点 ,p的左节点即
			//t[p]-1也有可能装下物品,此时t[p]-1和t[p]均能装下物品,但t[p]大于t[p]-1
			p *= 2;//默认左子树是赢者
		}
		int b;
		p /= 2;
		if (p < n) {
			b = W->Winner(p);
			if (b > 1 && avail[b - 1] >= s[i])
				b--;
		} else
			b = W->Winner(p / 2);
		cout << "Pack object " << i << " in bin " << b << endl;
		avail[b] -= s[i];
		W->Replay(b, winner);
	}
}

int main() {
	int n, c;
	cout << "Enter number of objects and bin capacity\n";
	cin >> n >> c;
	int*s = new int[n + 1];
	for (int i = 1; i <= n; i++) {
		while (1) {
			cout << "Enter space requirement of object" << i << endl;
			cin >> s[i];
			if (s[i] > c)
				cout << "Object too large to fit in a bin" << endl;
			else
				break;
		}
	}
	FirstFitPack(s, n, c);
	system("pause");
	return 0;
}
