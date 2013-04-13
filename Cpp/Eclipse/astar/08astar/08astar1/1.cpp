#include <cstdio>
using namespace std;

const int MAX = 100000;
int a[MAX];

int main()
{
	int i, j, d, n, p, sum;
	while(scanf("%d", &n) == 1)	{
		for(i = 0; i < n; i++)	scanf("%d", a+i);
		scanf("%d", &p);
		d = MAX+1;
		for(sum = j = i = 0; i < n; i++)	{
			sum += a[i];
			if(sum < p)	continue;
			while(sum >= p) sum -= a[j++];
			if(d >= i-j+1)	d = i-j+1;
		}
		printf("%d\n", d);
	}
	return 0;
}
			
