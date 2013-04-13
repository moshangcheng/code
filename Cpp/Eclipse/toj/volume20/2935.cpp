#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int main()
{
    int i, num_test, num;
    string s[10005];
    cin >> num_test;
    while(num_test-- > 0) {
        cin >> num;
        for(i = 0; i < num; i++) cin >> s[i];
        sort(s, s + num);
        for(i = 0; i < num - 1; i++)  
        if(s[i].length() <= s[i+1].length() &&
            s[i+1].compare(0, s[i].length(), s[i]) == 0) break;
        if( i == num - 1) cout << "YES\n";
        else cout << "NO\n";
    }
    return 0;
}
         
