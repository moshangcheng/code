#include <iostream>
#include <algorithm>
using namespace std;

struct cow {int m,first,second; };

bool operator<(cow a,cow b)
{ return (a.first>b.first); }

bool comp(cow a,cow b)
{ return (a.second<b.second); }

int main()
{
    int K,N;
    cow inf[50000];
    while(cin>>N>>K) {
        for(int i=0;i<N;i++) {
            cin>>inf[i].first>>inf[i].second;
            inf[i].m=i;
        }
        sort(inf,inf+N);
        cout<<(max_element(inf,inf+K,comp)->m)+1<<endl;        
    }
    return 0;
}
            
