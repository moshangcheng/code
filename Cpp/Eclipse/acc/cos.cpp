#include <cmath>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
using namespace std;

const double EP = 1e-6;
const double PI = 2*acos(0);
const double D = 10;
const char	 C = '*';
const int	 M = 31;
const int PERIOD = 1;

int main() 
{ 
	ostringstream oStr;
	int i, j, x, y, m; 
	//y为列方向，值从1到-1，步长为0.1
	for(y = D; y >= -D; y -= 1)
	{ 
		//计算出y对应的弧度m，乘以10为图形放大倍数 
		m = floor(acos(1.0*y/D)*M/PI);
		for(i = 0; i < PERIOD; i++)	{
			oStr << setw(m+1) << C;
			if(abs(y) != D)	{
				oStr << setw(2*(M-m)) << C;
				if(m > 1)	oStr << setw(m-1) << ' ';
			}
			else	oStr << setw(2*M-m-1) << ' ';
		}
		oStr << endl;
	}
	cout << oStr.str();
	system("pause");
	return 0;  
} 
