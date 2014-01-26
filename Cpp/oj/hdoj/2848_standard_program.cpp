/**
 * @author moshangcheng
 * @version 1.0
 * @date 2011-3-25 下午06:49:28
 * @brief http://acm.hdu.edu.cn/showproblem.php?pid=2848
 */
#include<iostream>
#include<map>
using namespace std;
long long h[22], N;
int K;
map<long long, int> ans;
int Dfs();
inline int ToL(long long p) {
	int ret = 0;
	while (p) {
		ret++;
		p /= 10;
	}
	return ret;
}
void solve(long long left, long long cnt, int last, int &val) {
	if (val)
		return;
	int len = ToL(left);
	if (len < last)
		return;
	if (last == 1) {
		cnt += left;
		N = cnt;
		if (!Dfs()) {
			val = 1;
			return;
		}
	}
	int half = len / 2, k;
	for (int i = 0; i <= len / 2 + 1; i++) {
		if (half + i < len) {
			k = half + i;
			if (k == 0)
				continue;
			solve(left / h[k], cnt + left % h[k], last - 1, val);
		}
		if (half - i - 1 >= 1) {
			k = half - i - 1;
			solve(left / h[k], cnt + left % h[k], last - 1, val);
		}
	}//这里不知道为什么，反正如果是从1到len枚举是过不了的，倒着枚举是300多MS，这样是203MS
}
int Dfs() {
	if (ans.find(N) != ans.end())
		return ans[N];
	int len = ToL(N);
	if (len < K)
		return 0;
	if (len < (K + K - 2))
		return 1;
	long long NN = N;
	int val = 0;
	solve(NN, 0, K, val);
	return ans[NN] = val;
}
int main() {
	h[0] = 1;
	for (int i = 1; i <= 18; i++)
		h[i] = h[i - 1] * 10;
	while (scanf("%I64d%d", &N, &K) != EOF) {
		ans.clear();
		printf("%d\n", Dfs());
	}
	return 0;
}
