#include <iostream>
#include <cmath>
using namespace std;

void pos(long long n,long long m,long long &x,long long &y)
{
    long long r,t=ceil(n-1/2.0-sqrt(n*n-m+1/4.0));
    long long s1=2*t*n-t*t,s2=n*(2*t+1)-t*(t+1);
    if(m<=s1) {
        r=n-t+m-s1;
        t*=2;
    }
    else {
        r=n-t+m-s2;
        t=2*t+1;
    }
    t--;
    switch(t%4) {
        case 0:
            x=r+t/4;
            y=1+t/4;
            break;
        case 1:
            x=n-t/4;
            y=r+1+t/4;
            break;
        case 2:
            x=n-r-t/4;
            y=n-t/4;
            break;
        case 3:
            x=t/4+1;
            y=n-r-t/4;
            break;            
    }
}

int main()
{
    long long m,p,n;
    long long mx,my,px,py,x,y;
    string s[3][3]={"Upper left","Up","Upper right",
                    "Left","\0","Right",
                    "Lower left","Down","Lower right"};
    while(cin>>n>>m>>p) {
        pos(n,m,mx,my);
        pos(n,p,px,py);
        x=(px<mx)?0:((px==mx)?1:2);
        y=(py<my)?0:((py==my)?1:2);
        cout<<s[x][y]<<endl;
    }
    return 0;
}
        
        
