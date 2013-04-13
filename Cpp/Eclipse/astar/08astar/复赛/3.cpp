#include <cstdio>
#include <list>
using namespace std;

const int MAX = 1000001;
int prt[MAX];
bool color[MAX];
list<int> E[MAX];

void Init(int e, int prev)	{
	list<int>::iterator cnt;
	for(cnt = E[e].begin(); cnt != E[e].end();)	{
		if(prev != 0 && *cnt == prev)
			cnt = E[e].erase(cnt);
		else {
			prt[*cnt] = e;
			Init(*cnt, e);
			cnt++;
		}
	}
}

int search(int e)	{
	int s = -1;
	while(e != 0)	{
		if(color[e])	s = e;
		e = prt[e];
	}
	return s;
}

int main()
{
	int n, c;
	int i, j, u, v;
	while(scanf("%d%d", &n, &c) == 2)	{
		for(i = 1;i < MAX; i++)	
			E[i].clear();
		memset(prt, 0, sizeof(prt));
		memset(color, 0, sizeof(color));
		for(i = 1; i < n; i++)	{
			scanf("%d%d", &u, &v);
			E[u].push_back(v);
			E[v].push_back(u);
		}
		Init(1, 0);
		for(i = 0; i < c; i++)	{
			scanf("%d%d", &u, &v);
			if(u == 0)
				color[v] = !color[v];
			else if(u == 1)
				printf("%d\n", search(v));
		}
	}
	return 0;
}
