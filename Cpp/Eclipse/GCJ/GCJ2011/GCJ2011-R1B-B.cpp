/********************************************************************
@created:	2011/05/05 17:16
@author:	moshangcheng
@version:	1.0
@tag:		GCJ2011
@purpose:	http://code.google.com/codejam/contest/dashboard?c=975485#s=p1
*********************************************************************/
#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <memory>
using namespace std;


double MINUS_INFINITY = -1.0e13;

int p[200];
int v[200];

//int tempTest(istream& cin, ostream& cout)	{
int main()	{
	int T, D, C;
	cin >> T;
	for(int i = 0; i < T; i++)	{
		cin >> C >> D;
		for(int j = 0; j < C; j++)	{
			cin >> p[j] >> v[j];
		}
		double cntPos = MINUS_INFINITY, maxTime = 0.0;
		for(int j = 0; j < C; j++)	{
			double extraTime = 0;
			double baseTime = (v[j]-1.0)*D/2.0;
			double dist = p[j]-baseTime-cntPos-D;
			if(maxTime < baseTime)	{
				if(dist < 0)	{
					extraTime = (-1.0*dist - (baseTime-maxTime))/2.0;
					if(extraTime < 0)	{
						extraTime = 0;
					}
				}
				maxTime = baseTime + extraTime;				
			}
			else	{
				if(dist < 0)	{
					extraTime = (-1.0*dist - (maxTime -baseTime))/2.0;
					if(extraTime < 0)	{
						extraTime = -dist;
					}
					else	{
						maxTime = maxTime + extraTime;
						extraTime = maxTime - baseTime;
					}
				}
				else	{
					extraTime = maxTime - baseTime;
					extraTime = dist > extraTime ? -1.0 * extraTime : -1.0 * dist;
				}
			}
			cntPos = p[j] + baseTime + extraTime;
		}
		cout << "Case #" << i+1 << ": ";
		cout.setf(ios::fixed);
		cout.precision(12);
		cout << maxTime << endl;
	}
	return 0;
}
