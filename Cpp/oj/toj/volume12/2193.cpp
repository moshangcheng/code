#include <iostream>
using namespace std;

int main()
{
    int N,n;
    while(cin>>N&&N) {
        cin>>n;
        if(N%(n+1)==0) cout<<"Think About It.\n";
        else cout<<"Just Do It.\n";
    }
    return 0;
}

