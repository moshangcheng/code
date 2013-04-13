//这是个错误的程序，aa a时也会输出Yes 
#include <iostream>
using namespace std;

int main()
{
    int i,j;
    string l,r;
    while(cin>>l>>r) {
        for(i=0,j=0;r[i]!='\0'&&l[j]!='\0';j++) 
        while(r[i]!='\0'&&r[i]!=l[j]) i++;
        if(r[i]=='\0') cout<<"No\n";
        else cout<<"Yes\n";
    }
    return 0;
}
        
    
