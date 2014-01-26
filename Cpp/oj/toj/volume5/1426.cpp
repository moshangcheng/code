#include <iostream>
using namespace std;

int main()
{
    char c;
    int b, M, R, m[10], p[1000], r[10], num_p, num_m, num_r, i, mi;
    while(cin >> b && b > 0) {
        cin.get(c);
        R = M = num_r = num_m = num_p = 0;
        while(cin.get(c) && c != ' ') p[num_p++] = c - '0';
        while(cin.get(c) && c != '\n') m[num_m++] = c - '0';
        for(i = num_m - 1, mi = 1; i > -1; i--, mi*= b) 
        M+= m[i] * mi;
        for(i = num_p - 1, mi = 1; i > -1; i--, mi = mi * b % M) 
        R = (R + p[i] * mi) % M; 
        if(R == 0) {
            cout << 0 << endl;
            continue;
        }
        for(mi = 1; mi <= R; num_r++, mi*= b);
        for(i = num_r - 1, mi/= b; i > -1; i--, R = R % mi, mi/= b) 
        r[i] = R / mi;
        for(i = num_r - 1; i > -1; i--) cout << r[i];
        cout << endl;
    }
    return 0;
}
        
