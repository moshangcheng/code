#include <iostream>
#include <string>
using namespace std;

int main()
{
    string ss, s, es;
    while(cin >> ss && ss != "ENDOFINPUT") {
        getline(cin, ss);
        getline(cin, s);
        getline(cin, es);
        for(int i = 0; i <s.size(); i++)
        if(s[i] >= 'A' && s[i] <= 'Z') 
        s[i] = (s[i] - 'A' + 21)% 26 + 'A';
        cout << s << endl;
    }
    return 0;
}
