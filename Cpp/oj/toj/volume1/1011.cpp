#include <iostream>
#include <iomanip>
using namespace std;

struct Edge{
    int x;
    int y;
};

struct Point{
    int x;
    int y;
};

int GCD(int m,int n)
{
    if(m<0) m=-m;
    if(n<0) n=-n;
    while(m>0){
        int c=n%m;
        n=m;
        m=c; 
    }
    return n;
}

int main()
{
    int m,n=0,num;
    int I,E,A;
    cin>>m;
    while(n<m){
        cin>>num;
        I=E=A=0;
        Edge* e=new Edge[num];
        Point* p=new Point[num];
        for(int i=0;i<num;i++) {
            cin>>e[i].x>>e[i].y;
            if(i==0){
                p[i].x=e[i].x;
                p[i].y=e[i].y;
            }
            else {
                p[i].x=e[i].x+p[i-1].x;
                p[i].y=e[i].y+p[i-1].y;
            }
        }
        for(int i=0;i<num;i++) {
            E+=GCD(e[i].x,e[i].y);
            A+=p[i].x*p[(i+1)%num].y-p[i].y*p[(i+1)%num].x;
        }
        if(A<0) A=-A;
        I=(A-E)/2+1;
        double a=A/2.0;
        cout<<"Scenario #"<<++n<<":\n";
        cout<<I<<" "<<E<<" ";
        cout.setf(ios::fixed);
        cout<<setprecision(1)<<a<<endl<<endl;
        delete [] e;
        delete [] p;
    }
    return 0;
}
            
            
        
        
        
