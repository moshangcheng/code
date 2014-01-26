#include <iostream>
#include <string>
using namespace std;

int main()
{
    int n,num;
    int num_case,i_case=0;
    string samp="sheep",s;
    
    cin>>num_case;
    while(i_case++<num_case) {
        cin>>n;
        num=0;
        for(int i=0;i<n;i++) {
            cin>>s;
            if(s.compare(samp)==0) num++;
        }
        cout<<"Case "<<i_case<<": This list contains "<<num<<" sheep.\n";
        if(i_case<num_case) cout<<endl;
    }
    return 0;
}
