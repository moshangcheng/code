#include <cstdio>
#include <cstring>
using namespace std;

const int MAX = 10001;
int h[MAX], s[MAX];

int main()
{
	int ntest;
	int i, j, L, N, D;
	scanf("%d", &ntest);
	while(ntest-- > 0) {
		scanf("%d%d%d", &L, &N, &D);
		memset(h, 0, sizeof(h));
		for(i = 0; i < N; i++)  {
			scanf("%d", &j);
			scanf("%d", h+j);
		}
		for(i = 0; i <= L; i++) {
			if(i > D) 	s[i] = s[i-D-1] + h[i];
			else 		s[i] = h[i];
			if(i > 0 && s[i] < s[i-1]) s[i] = s[i-1];
		}
		printf("%d\n", s[L]);
	}
	return 0;
}
