#include <iostream>
#include <cmath>
using namespace std;

const double INF = 1e+100;
const int BASE = 50;
struct CIRCLE	{
	int x, y, r;
};

CIRCLE cir[100]; 

inline double dist(double x1, double y1, int j)
{
	return sqrt((cir[j].x-x1)*(cir[j].x-x1)+(cir[j].y-y1)*(cir[j].y-y1));
}

int main()
{
	int i, j, k;
	int x, y, n, L, W;
	double d, mink, cntk;
	while(cin >> n >> L >> W)	{
		for(i = 0; i < n; i++)
			cin >> cir[i].x >> cir[i].y >> cir[i].r;
		mink = 0;
		for(i = 0; i <= BASE*L; i++)	{
			cntk = INF;
			for(j = 0; j < n; j++)	{
				d = dist(1.0*i/BASE, 0, j);
				if(d < cntk*cir[j].r)	cntk = d/cir[j].r;
			}
			if(cntk > mink)	mink = cntk;
		}
		for(i = 0; i <= BASE*W; i++)	{
			cntk = INF;
			for(j = 0; j < n; j++)	{
				d = dist(L, 1.0*i/BASE, j);
				if(d < cntk*cir[j].r)	cntk = d/cir[j].r;
			}
			if(cntk > mink)	mink = cntk;
		}
		for(i = 0; i <= BASE*L; i++)	{
			cntk = INF;
			for(j = 0; j < n; j++)	{
				d = dist(1.0*i/BASE, W, j);
				if(d < cntk*cir[j].r)	cntk = d/cir[j].r;
			}
			if(cntk > mink)	mink = cntk;
		}
		for(i = 0; i <= BASE*W; i++)	{
			cntk = INF;
			for(j = 0; j < n; j++)	{
				d = dist(0, 1.0*i/BASE, j);
				if(d < cntk*cir[j].r)	cntk = d/cir[j].r;
			}
			if(cntk > mink)	mink = cntk;
		}
		cout.setf(ios::fixed);
		cout.precision(3);
		cout << mink << endl;
	}
	return 0;
}
