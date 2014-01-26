#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

void pos(long long n,long long m,int &x,int &y)
{
    //s[2t]=2tn-t^2; s[2t+1]=n^2-(n-t)(n-t-1);
    //s[2t-1]<m<=s[2t+1] 即在s[2t]和s[2t+1]范围内的点
    //(n-t)(n-t-1)<=n^2-m<(n-t+1)(n-t)
    //n-t-1/2<=sqrt(n^2-m+1/4)<n-t+1/2
    //t-1<n-1/2-sqrt(n^2-m+1/4)<=t
    int r,t=ceil(n-1/2.0-sqrt(n*n-m+1/4.0));
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
    long long n,m,p;
    int mx,my,px,py;
    while(cin>>n) {
        int x,y,a[100][100];
        for(int i=1;i<=n*n;i++) {
            pos(n,i,x,y);
            a[x-1][y-1]=i;
        }
        for(int i=0;i<n;i++) {
            for(int j=0;j<n;j++) cout<<setw(3)<<a[i][j]<<" ";
            cout<<endl;
        }
    }
    /*while(cin>>n>>m>>p) {
        pos(n,m,mx,my);
        pos(n,p,px,py);
        if(px<mx) cout<<"Upper";
        else if(px>mx) cout<<"Down";
        if(px!=mx&&py!=my) cout<<' ';
        if(py>my) cout<<"Right";
        else if(py<my) cout<<"Left";
        cout<<endl;
    }*/
    return 0;
}
        
        
