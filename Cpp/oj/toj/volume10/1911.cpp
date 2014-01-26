#include <iostream>
#include <string>
using namespace std;

int main()
{
    string s;
    int i, nv, cv, cc, cl;
    bool c[26];
    memset(c, 0, sizeof(c));
    c['a'-'a'] = c['e'-'a'] = c['i'-'a'] = c['o'-'a'] = c['u'-'a'] = 1;
    while(cin >> s && s != "end") {
        nv = cv = cc = cl = 0;
        if(c[s[0] - 'a']) cv = nv = 1;
        else cc = 1;
        cl = 1;
        for(i = 1; i < s.size(); i++) {
            if(c[s[i] - 'a']) {
                nv++;   cv++;  cc = 0;
                if(cv > 2) break;
            }
            else {
                cc++;  cv = 0;
                if(cc > 2) break;
            }
            if(s[i] == s[i-1]) cl++;
            else cl = 1;
            if(cl > 1 && s[i] != 'e' && s[i] != 'o') break;
        }
        cout << "<" << s << "> ";
        if(nv == 0 || i < s.size()) cout << "is not acceptable.\n";
        else cout << "is acceptable.\n";
    }
    return 0;
}

