#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

int main() 
{
    char t;
    double l=0;
    int h,m,s,hh,mm,ss,speed=0;
    while(cin>>hh>>t>>mm>>t>>ss) {
        t=cin.get();
        if(speed) l+=((hh-h)+(mm-m)/60.0+(ss-s)/3600.0)*speed;
        if(t!='\n') cin>>speed;
        else {
            cout.setf(ios::fixed);
            if(hh<10) cout<<0;
            cout<<hh<<':';
            if(mm<10) cout<<0;
            cout<<mm<<':';
            if(ss<10) cout<<0;
            cout<<ss<<' '<<setprecision(2)<<l<<" km\n";
        }
        h=hh; s=ss; m=mm;
    }
    return 0;
}
    
