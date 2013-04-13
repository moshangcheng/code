#include <iostream>
#include <fstream>
#include <ctime>
using namespace std;

const int SIZE = 10000;//数组大大小 
const int T = 10000;//设定程序重复执行的次数 

int main()
{
	int A[SIZE], B[SIZE];
	ifstream in("in.txt");
	
	//从文件输入数据 
	for(int i = 0; i < SIZE; i++)	{
		in >> A[i];
	}
	for(int i = 0; i < SIZE; i++)	{
		in >> B[i];
	}
	
	clock_t start, end;//记时变量 
	
	cout << "数据规模 " << SIZE << endl; 
	cout << "程序执行 " << T << "次\n\n"; 
	
	//采用一般的合并方法 
	cout << "采用合并排序的方法获得中位数\n";
	start = clock();
	for(int l = 0; l < T; l++)	{
		int i, j, k;
		for(i = j = k = 0; i <= SIZE; i++)	{
			if(A[j] < B[k]) j++;
			else			k++;
		}
		j--;
		k--;
		if(l > 0)	continue;
		if(A[j] > B[k])	{
			if(j > 0 && A[j-1] > B[k])	
			cout << "A[" << j-1 << "] = " << A[j-1] << " , ";
			else	cout << "B[" << k << "] = " << B[k] << " , ";
			cout << "A[" << j << "] = " <<A[j] << endl;
		}
		else if(A[j] < B[k])	{
			if(k > 0 && B[k-1] > A[j])	
			cout << "B[" << k-1 << "] = " << B[k-1] << " , ";
			else	cout << "A[" << j << "] = " << A[j] << " , ";
			cout << "B[" << k << "] = " << B[k] << endl;
		}
	}
	end = clock();
	cout << (end - start) << " ms" << endl << endl; 
	
	//采用二分查找的方法 
	cout << "采用二分查找的方法获得中位数\n"; 
	start = clock();
	for(int l = 0; l < T; l++)	{
		int m, n;//游标 
		int down_a, down_b, up_a, up_b;//中位数所在的区域 
		down_a = down_b = 0;
		up_a = up_b = SIZE-1;
		m = (up_a + down_a + 1)/2;
		n = (up_b + down_b)/2;	
		while(1)	{	
			if(A[m] > B[n])	{
				up_a = m;
				down_b = n;	
				if(n == SIZE-1 || A[m] < B[n+1]) {
					if(l == 0)	{
						if(m > 0 && A[m-1] > B[n])	
						cout << "A[" << m-1 << "] = " << A[m-1] << " , ";
						else	cout << "B[" << n << "] = " << B[n] << " , ";
						cout << "A[" << m << "] = " <<A[m] << endl;
					}
					break;
				}
				m = (up_a + down_a)/2;
				n = (up_b + down_b + 1)/2;	
			}
			else if(A[m] < B[n])	{
				down_a = m;
				up_b = n;
				if(m == SIZE-1 || B[n] < A[m+1]) {
					if(l == 0)	{
						if(n > 0 && B[n-1] > A[m])	
						cout << "B[" << n-1 << "] = " << B[n-1] << " , ";
						else	cout << "A[" << m << "] = " << A[m] << " , ";
						cout << "B[" << n << "] = " << B[n] << endl;
					}
					break;
				}
				m = (up_a + down_a + 1)/2;
				n = (up_b + down_b)/2;	
			}
		}
	}
	end = clock();
	cout << (end - start) << " ms" << endl << endl; 
	
	
	system("pause");
	return 0;
}
	
