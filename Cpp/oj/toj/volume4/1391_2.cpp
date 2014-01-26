#include <iostream>
#include <string>
using namespace std;

struct price { string s; int n;};

int main()
{
    int M,N,sum;
    string str;
    price s[1000];
    while(cin>>M>>N) {
        for(int i=0;i<M;i++) cin>>s[i].s>>s[i].n; 
        for(int j=0;j<N;j++) {
            sum=0;
            while(cin>>str&&str[0]!='.') 
            for(int i=0;i<M;i++) if(str.compare(s[i].s)==0) sum+=s[i].n;
            cout<<sum<<endl;
        }
    }
    return 0;
}
        
        
    
    
