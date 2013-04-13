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

int w[100];
int op[100];
double owp[100];
double oowp[100];
int match[100][100];

//int tempTest(istream& cin, ostream& cout)	{
int main()	{
	int T, N;
	cin >> T;
	for(int i = 0; i < T; i++)	{
		cin >> N;
		for(int j = 0; j < N; j++)	{
			w[j] = 0;
			op[j] = 0;
			string tempMatch;
			int valueSum = 0, matchSum = 0;
			cin >> tempMatch;
			for(int k = 0; k < N; k++)	{
				if(tempMatch[k] == '0')	{
					op[j]++;
					match[j][k] = -1;
				}
				else if(tempMatch[k] == '1')	{
					w[j]++;
					op[j]++;					
					match[j][k] = 1;					
				}
				else {
					match[j][k] = 0;
				}
			}			
		}
		//¼ÆËãowp
		for(int j = 0; j < N; j++)	{
			double tempSum = 0;
			for(int k = 0; k < N; k++)	{
				if(k == j || match[k][j] == 0)	{
					continue;
				}
				if(match[k][j] == 1)	{
					tempSum += (w[k]-1.0)/(op[k]-1.0);
				}
				else if(match[k][j] == -1)	{
					tempSum += w[k]/(op[k]-1.0);
				}
			}
			owp[j] = tempSum/op[j];
		}
		//¼ÆËãoowp
		for(int j = 0; j < N; j++)	{
			double tempSum = 0;
			for(int k = 0; k < N; k++)	{
				if(k == j || match[k][j] == 0)	{
					continue;
				}				
				tempSum += owp[k];
			}
			oowp[j] = tempSum/op[j];
		}
		cout << "Case #" << i+1 << ":\n";
		cout.setf(ios::fixed);
		cout.precision(12);
		for(int j = 0; j < N; j++)	{
			cout << 0.25*w[j]/op[j] + 0.5*owp[j] + 0.25*oowp[j]<<"\n";
		}
	}
	return 0;
}
