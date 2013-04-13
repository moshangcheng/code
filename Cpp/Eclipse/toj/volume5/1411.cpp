#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

struct point { int x,y; };
const double MAX=1E+10;
inline double dist(point a,point b)
{ return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y)); }

int main()
{
    int N,S,P;
    point p[500];
    double d[500];
    bool visited[500];
    cin>>N;
    while(N-->0) {
        cin>>S>>P;
        for(int i=0;i<P;i++) {
            cin>>p[i].x>>p[i].y;
            visited[i]=0;
            d[i]=dist(p[0],p[i]);
        }
        
        int maxp,minp;
        double mind;
        for(int k=0;k<S;k++)  {
            maxp=0;
            for(int i=0;i<P;i++) visited[i]=0;
            for(int i=1;i<P;i++) {
                mind=MAX;
                for(int j=1;j<P;j++) 
                if(visited[j]==0&&d[j]<mind) {
                    minp=j;
                    mind=d[j];
                }
                visited[minp]=1;
                if(mind>d[maxp]) maxp=minp;
                for(int j=1;j<P;j++) {
                    if(visited[j]==0) {
                        double temp=dist(p[minp],p[j]);
                        temp=mind>temp?mind:temp;
                        if(d[j]>temp) d[j]=temp;
                    }
                }
            }
            if(k<S-1) d[maxp]=0;
        }
        cout.setf(ios::fixed);
        cout<<setprecision(2)<<d[maxp]<<endl;
    }
    return 0;
}
        
                
            
        
        
    
