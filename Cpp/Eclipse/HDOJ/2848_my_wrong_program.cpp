/**
 * @author moshangcheng
 * @version 1.0
 * @date 2011-3-25 下午06:49:28
 * @brief http://acm.hdu.edu.cn/showproblem.php?pid=2848
 */
#include <cmath>
#include <map>
#include <fstream>
#include <cstdio>
using namespace std;

int k;
const long long MAX = 20;
long long Pow10[MAX];
map<long long, int> storedSG;

int sg(long long n);
int dfs(long long n, long long sum, int cnt, int res);

inline int getLength(long long n) {
	int len = 0;
	for (; n; len++) {
		n /= 10;
	}
	return len;
}

void init() {
	Pow10[0] = 1;
	for (int i = 1; i < MAX; i++) {
		Pow10[i] = Pow10[i - 1] * 10;
	}
}

int dfs(long long n, long long sum, int cnt, int res) {
	if (res > cnt) {
		return 0;
	}
	if (res == 1 && cnt >= 1) {
		sum += n % Pow10[cnt];
		sg(sum);
		//printf("%lld | %d\n", sum, storedSG[sum]);
		return !storedSG[sum];
	} else {
		bool flag = 0;
		for (int i = cnt - 1; i >= res - 1; i--) {
			flag = flag | dfs(n, sum + n % Pow10[cnt] / Pow10[i], i, res - 1);
			if (flag) {
				return flag;
			}
		}
	}
	return 0;
}

int sg(long long int n) {
	if (storedSG.find(n) != storedSG.end()) {
		return storedSG[n];
	}
	int len = getLength(n);
	if (len < k) {
		return storedSG[n] = 0;
	}
	return storedSG[n] = dfs(n, 0, getLength(n), k);
}

int main() {
	long long n;
	init();

	while (scanf("%lld%d", &n, &k) == 2) {
		storedSG.clear();
		printf("%d\n", sg(n));
	}
	/*
	 ifstream in("in.txt");
	 ofstream out("myOut.txt");
	 while (in >> n >> k) {
	 storedSG.clear();
	 out << sg(n) << endl;
	 }
	 */
	return 0;
}
