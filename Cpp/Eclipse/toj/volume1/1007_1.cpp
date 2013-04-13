#include <stdio.h>
int test(int m, int N)
{
	int i, p;

        m--;	

        i=0;
	for(p = 2*N; p>N; p--){
		i = (i+m) % p;
		if(i<N) return 0;
	}

	return 1;
}

int main()
{
	int m, N;
	while(scanf("%d",&N))
	{
		for(m = 1; ; m++)
		{
			if(test(m, N))
			{
				printf("%d\n", m);
				break;
			}
		}
		
	}
	return 0;
}
