#include <iostream>
#include <cmath>
using namespace std;

int a[6][2] = {1, 0, 0, 1, -1, 1, -1, 0, 0, -1, 1, -1};
int b[6][2] = {-1, 1, -1, 0, 0, -1, 1, -1, 1, 0, 0, 1};

int main()
{
	int x, y, s, u, v, n, m;
	while(cin >> n)	{
		//计算六边形的边长 m 
		m = ceil(sqrt(((n-1.0)/3.0+ 0.25))-0.5);
		if(m == 0) {
			cout << 0 << " " << 0 << endl;
			continue;
		} 
		//边长 m 的六边形上 的第一个点序号
		s = 1 + 3*m*(m-1);
		u = (n-s)/m%6;
		v = (n-s)%m;
		x = a[u][0]*m + b[u][0]*v;
		y = a[u][1]*m + b[u][1]*v;
		cout << x << " " << y << endl;
	}
	return 0;
}
