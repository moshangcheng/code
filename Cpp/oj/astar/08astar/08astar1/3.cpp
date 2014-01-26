#include<cstdio>
#include<set>
#include<algorithm>
using namespace std;
set<pair<int,int> > ST;
set<pair<int,int> >::iterator it;
int N,M;
pair<int,int> pp;
int z[200000];
int main()
{
    int i,j;
    int a,b,c,d;
    int ans,x,r;
    scanf("%d%d",&N,&M);
    for(i=1;i<=N;i++) {
        scanf("%d",&d);
        pp=make_pair(d,i);
        ST.insert(pp);
        z[i]=d;
    }
    while(M--) {
        scanf("%d",&a);
        if(a==0) {
            scanf("%d%d",&b,&c);
            pp=make_pair(z[b],b);
            it=ST.find(pp);
            ST.erase(it);
            pp=make_pair(c,b);
            ST.insert(pp);
            z[b]=c;
        }else {
            scanf("%d%d%d",&b,&c,&d);
            it=ST.upper_bound(make_pair(d,N));
            it--;
            ans=0;
            while(true) {
                pp=*it;
                r=pp.second;
                x=pp.first;
                if(b<=r && r<=c) {
                    if(d>=x) {
                        ans=x;
                        break;
                    }
                }
                if(it==ST.begin()) break;
                it--;
            }
            printf("%d\n",ans);
        }
    }
    return 0;
}
