#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int main()
{
    char c;
    string s;
    int i, j;
    while(cin >> s) {
        for(i = s.size() - 2; i >= 0; i--)
            if(s[i] < s[i+1]) break;
        if(i < 0) cout << 0 << endl;
        else {
            for(j = i+1; j < s.size(); j++)
                if(s[j] <= s[i]) break;
            c = s[j-1];    s[j-1] = s[i];   s[i] = c;
            reverse(s.begin()+i+1, s.end());
            cout << s << endl;
        }
    }
    return 0;
}
            
        
