/********************************************************************
@created:	2011/05/05 17:16
@author:	moshangcheng
@version:	1.0
@tag:		GCJ2011
@purpose:	http://code.google.com/codejam/
*********************************************************************/
#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <memory>
using namespace std;

int n;
int R, C;
char color[50][50];

bool flag;

bool dfs()	{
	if(n == 0)	{		
		return flag = true;
	}
	for(int i = 0; i < R; i++)	{
		for(int j = 0; j < C; j++)	{
			if(color[i][j] == '#' && i+1 < n && j+1 < n && color[i+1][j] == '#' && color[i][j+1] == '#' && color[i+1][j+1] == '#')	{
				n -= 4;
				color[i][j] = color[i+1][j+1] = '/';
				color[i+1][j] = color[i][j+1] = '\\';
				if(dfs())	{
					return true;
				}
				color[i][j] = color[i+1][j] = color[i][j+1] = color[i+1][j+1] = '#';
				n += 4;
			}
		}
	}
	return false;
}

//int tempTest(istream& cin, ostream& cout)	{
int main()	{
	int T;
	cin >> T;
	for(int i = 0; i < T; i++)	{
		n = 0;
		flag = false;
		cin >> R >> C;
		for(int j = 0; j < R; j++)	{
			for(int k = 0; k < C; k++)	{				
				cin >> color[j][k];
				if(color[j][k] == '#')	{
					n++;					
				}
			}
		}
		dfs();
		cout << "Case #" << i+1 << ":\n";
		if(flag)	{
			for(int j = 0; j < R; j++)	{
				for(int k = 0; k < C; k++)	{
					cout << color[j][k];
				}
				cout << "\n";
			}
		}
		else	{
			cout << "Impossible\n";
		}
	}
	return 0;
}
