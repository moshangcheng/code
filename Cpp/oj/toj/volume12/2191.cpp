#include <iostream>
#include <fstream>
using namespace std;

struct card  { int  c,v; } ;

void convert(string a,card &b)
{
    if(a[0]=='C')      b.c=0;
    else if(a[0]=='D') b.c=1;
    else if(a[0]=='H') b.c=2;
    else if(a[0]=='S') b.c=3;
    if(a[1]=='J')      b.v=9;
    else if(a[1]=='Q') b.v=10;
    else if(a[1]=='K') b.v=11;
    else if(a[1]=='A') b.v=12;
    else if(a[1]=='1') b.v=8;
    else b.v=int(a[1])-int('2');
}

void sort(card c[3])
{
    for(int i=0;i<3;i++)
    for(int j=i+1;j<3;j++)
    if(c[i].v<c[j].v) {
        card temp=c[i];
        c[i]=c[j];
        c[j]=temp;
        
    }
}

int rank(card c[3])
{ 
    if(c[0].v==c[1].v&&c[1].v==c[2].v) return 5;
    else if(c[0].c==c[1].c&&c[1].c==c[2].c) {
        if((c[1].v==c[0].v-1)&&(c[2].v==c[1].v-1)) return 4;
        else return 3;
    }
    else if((c[1].v==c[0].v-1)&&(c[2].v==c[1].v-1)) return 2;
    else if(c[1].v==c[0].v||c[1].v==c[2].v)
    return 1;
    else return 0;
}

int main()
{
    string L[3],R[3];
    card l[3],r[3];
    ifstream in("C:\\Documents and Settings\\moshangcheng\\桌面\\in.txt");
    while(in>>L[0]>>L[1]>>L[2]>>R[0]>>R[1]>>R[2]) {
        for(int i=0;i<3;i++) {
            convert(L[i],l[i]);
            convert(R[i],r[i]);
        }
        sort(l);
        sort(r);
        int rr=rank(r)*2197+r[0].v*169+r[1].v*13+r[2].v;
        int rl=rank(l)*2197+l[0].v*169+l[1].v*13+l[2].v;
        if(rl>rr) cout<<"Win\n";
        else if(rl<rr) cout<<"Lose\n";
        else cout<<"Tie\n";          
    }
    system("pause");
    return 0;
}
        
