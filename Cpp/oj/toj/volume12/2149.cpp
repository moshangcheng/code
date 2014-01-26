#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int main()
{
    int ntest, i, sum, cr, len, otest = 0;
    string a, b, c;
    cin >> ntest;
    while(otest < ntest) {
        c.erase();
        cin >> a >> b;
        reverse(a.begin(), a.end());
        reverse(b.begin(), b.end());
        len = (a.size() > b.size()) ? a.size(): b.size();
        a.append(len - a.size(), '0');
        b.append(len - b.size(), '0');
        for(i = cr = sum = 0; i < len; i++) {
            sum = a[i] + b[i] + cr - 2*('0');
            cr = sum/2;
            c += (char)(sum % 2 + '0');
        }
        if(cr > 0) c += '1';
        for(i = c.size(); i > 1 && c[i-1] == '0'; i--);
        c.erase(i);
        reverse(c.begin(), c.end());
        cout << ++otest << " " << c << endl;
    }
    return 0;
}
                
