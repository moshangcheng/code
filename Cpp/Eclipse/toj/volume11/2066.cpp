#include <iostream>
#include <string>
using namespace std;

int main()
{
    int len, ntest;
    string a, b;
    cin >> ntest;
    while(ntest-- > 0)  {
        cin >> a >> b;
        len = (a.size() > b.size()) ?  a.size(): b.size();
        a.insert(0, len - a.size(), '0');
        b.insert(0, len - b.size(), '0');
        if(a >= b) cout << "MMM BRAINS\n";
        else cout << "NO BRAINS\n";
    }
    return 0;
}
