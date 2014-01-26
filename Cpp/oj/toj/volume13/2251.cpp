#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

const double INF = 1e200;
const double EP  = 1e-10;

double p[30][2];
double d[30][30];

double dist(int p1, int p2)
{
	double d = 0;
	d += (p[p1][0]-p[p2][0])*(p[p1][0]-p[p2][0]);
	d += (p[p1][1]-p[p2][1])*(p[p1][1]-p[p2][1]);
	return sqrt(d);
}

bool cir(int p1, int p2, int p3) 
{
	double a1  = 2*(p[p2][0] - p[p1][0]);
	double a2  = 2*(p[p3][0] - p[p1][0]);
	double b1  = 2*(p[p2][1] - p[p1][1]);
	double b2  = 2*(p[p3][1] - p[p1][1]);
	double c1  = p[p1][0]*p[p1][0] + p[p1][1]*p[p1][1];
	double c2  = c1;
	c1 -= p[p2][0]*p[p2][0] + p[p2][1]*p[p2][1];
	c2 -= p[p3][0]*p[p3][0] + p[p3][1]*p[p3][1];
	double a   = a1*b2 - a2*b1;
	double b   = c2*b1 - c1*b2;
	double c   = c1*a2 - c2*a1;
	if(fabs(a) < EP) return 0;
	p[26][0] = b/a;
	p[26][1] = c/a;
	return 1;
}

int main()
{
	string tmp;
	vector<string> L;
	int i, j, k, l, np;
	double r, A, B, C, D;
	while(cin >> np && np > 0) {
		L.clear();
		for(i = 0; i < np; i++) 
			cin >> p[i][0] >> p[i][1];
		for(i = 0; i < np; i++)
		for(j = 0; j < np; j++) 
			d[i][j] = dist(i, j);
		for(i = 0; i < np; i++)
		for(j = i+1; j < np; j++) 
		for(k = j+1; k < np; k++) {
			if(cir(i, j, k) == 0)  continue;
			for(l = k+1; l < np; l++) {
				if(fabs(dist(l, 26) - dist(i, 26)) < EP)  {
					tmp.clear();
					tmp += (i+'A');
					tmp += (j+'A');
					tmp += (k+'A');
					tmp += (l+'A');
					L.push_back(tmp);
				}
			}
		}
		cout << L.size() << endl;
		for(i = 0; i < L.size(); i++)
			cout << L[i] << endl;
	}
	return 0;
}
		
