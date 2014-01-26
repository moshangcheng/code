#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;

bool cmp(int a, int b)	{
	return abs(a) > abs(b);
}

int main()
{
	int i, j, k, l, n1, n2, n3, N, K;
	int vlu[100], pst[100], ngt[100];
	while(cin >> N >> K)	{
		for(i = 0; i < N; i++)
			cin >> vlu[i];
		sort(vlu, vlu+N , cmp);
		for(i = n1 = n2 = n3 = 0; i < N; i++)	{
			if(vlu[i] < 0)		ngt[n1++]  = vlu[i];
			else if(vlu[i] > 0)	pst[n2++]  = vlu[i];
			else				n3++;
		}
		for(i = j = k = l = 0; i < K; i++)	{
			if(vlu[i] < 0)		j++;
			else if(vlu[i] > 0)	k++;
			else				l++;			
		}
		if(l == 0 && (j&1) == 1)	{
			if(j == n1 && k == n2)	{
				l++;
				j--;
			}
			else if(j == n1)	{
				j--;
				k++;
			}
			else if(k == n2)	{
				if(k > 0)	{
					j++;
					k--;
				}
				else if(k == 0)	{
					if(n3 > 0)	{
						j--;
						l++;
					}
				}
			}
			else	{
				int s1 = ngt[j-1]*ngt[j];
				int s2 = pst[k-1]*pst[k];
				if(s1 <= s2)	{
					j--;
					k++;
				}
				else	{
					j++;
					k--;
				}
			}
		}
		if(l == 0 && k == 0 && (j&1) == 1)	{
			for(i = n1-1; K > 0; K--, i--)	{
				cout << ngt[i];
				if(K > 1)	cout << " ";
			}
		}
		else {
			for(i = 0; i < k; K--, i++)	{
				cout << pst[i];
				if(K > 1)	cout << " ";
			}
			for(i = 0; i < l; K--, i++)	{
				cout << 0;
				if(K > 1)	cout << " ";
			}
			for(i = j-1; i >= 0; K--, i--)	{
				cout << ngt[i];
				if(K > 1)	cout << " ";
			}
		}
		cout << endl;
	}
	return 0;
}
