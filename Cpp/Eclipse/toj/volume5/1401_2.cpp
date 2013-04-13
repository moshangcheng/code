#include <iostream>
#include <string>
using namespace std;
int main()
{
    string a,b;
    while(cin>>a>>b)
    {
        int n=0,num=0;
        for (int i=0;i<a.length();i++)
        {
            for (int j=num;j<b.length();j++)
            {
                if (b[j]==a[i]) 
                {
                    num=j;
                    n++;
                    break;
                }
            }
        }
    if (n==a.length()) cout<<"Yes\n";
    else cout<<"No\n";
    }
    return 0;
}
