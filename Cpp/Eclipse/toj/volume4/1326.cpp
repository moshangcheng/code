#include <iostream>
#include <string>
using namespace std;

int main()
{
    string s;
    int c[26]={0,1,2,3,0,1,2,0,0,2,2,4,5,5,0,1,2,6,2,3,0,1,0,2,0,2};
    while(cin>>s) {
        for(int i=0;s[i]!='\0';i++) 
        if(c[s[i]-'A']&&(i==0||c[s[i]-'A']!=c[s[i-1]-'A'])) cout<<c[s[i]-'A'];
        cout<<endl;
    }
    return 0;
}
