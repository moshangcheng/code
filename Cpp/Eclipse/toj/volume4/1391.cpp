#include <iostream>
#include <string>
#include <fstream>
#include <map>
using namespace std;

struct ltstr
{
  bool operator()(const char* s1, const char* s2) const
  {
    return strcmp(s1, s2) < 0;
  }
};

int main()
{
    ifstream in("C:\\Documents and Settings\\moshangcheng\\桌面\\in.txt");
    int M,N,val,sum;
    char str[16];
    map<const char*,int,ltstr> s;
    while(in>>M>>N) {
        for(int i=0;i<M;i++) { 
            in>>str>>val; 
            s[str]=val ;
            cout<<str<<" "<<s[str]<<endl;
        }
        s["."]=0;
        for(int j=0;j<N;j++) {
            sum=0;
            while(in>>str&&str[0]!='.') {
                sum+=s[str];
                cout<<str<<" "<<s[str]<<" "<<sum<<endl;
            }
            cout<<sum<<endl;
        }
    }
    system("pause");
    return 0;
}
        
        
    
    
