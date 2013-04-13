#include <iostream>
using namespace std;

int main()
{
    int page,sheet;
    while(cin>>page&&page>0) {
        sheet=(page-1)/4+1;
        cout<<"Printing order for "<<page<<" pages:\n";
        for(int i=1;i<=sheet;i++) {
            cout<<"Sheet "<<i<<", front: ";
            if(4*sheet-2*i+2>page)cout<<"Blank, ";
            else cout<<4*sheet-2*i+2<<", ";
            cout<<2*i-1<<endl;
            if(i==sheet&&2*i>page) break;
            cout<<"Sheet "<<i<<", back : ";
            cout<<2*i<<", ";
            if(4*sheet-2*i+1>page)
            cout<<"Blank\n";
            else cout<<4*sheet-2*i+1<<endl;
        }
    }
    return 0;
}
