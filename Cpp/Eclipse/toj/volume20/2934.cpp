#include <iostream>
#include <list>
#include <algorithm>
using namespace std;

struct cow {int m,first,second; };

bool operator<(cow a,cow b)
{ return (a.first>b.first); }

int main()
{
    int K,N;
    list<cow> L;
    list<cow>::iterator cnt;
    while(cin>>N>>K) {
        cow x;
        for(int i=0;i<N;i++) {
            cin>>x.first>>x.second;
            x.m=i;
            L.push_back(x);
        }
        L.sort();
        int max=-1,order;
        list<cow>::iterator cnt=L.begin();
        for(int i=0;i<K;i++,cnt++) 
        if(cnt->second>max) {
            order=cnt->m;
            max=cnt->second;
        }
        cout<<order+1<<endl;
    }
    return 0;
}
            
