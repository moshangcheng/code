#include <iostream>
using namespace std;

int len, depth, d[100], vlu[100], end[100];

int main()
{
    int i, j, S, C, ntest;
    cin >> ntest;
    while(ntest-- > 0)  {
        cin >> S >> C;
        for(i = 0; i < S; i++) cin >> vlu[i];
        len = S;    depth = 0;
        for(i = 0; i < S; i++) d[i] = vlu[i];
        while(1) {
            end[depth++] = d[len-1];
            for(i = 1; i < len && d[i] == d[i-1]; i++);
            if(i == len) break;
            for(i = 1; i < len; i++) d[i-1] = d[i] - d[i-1];
            len--;
        }
        for(i = 0; i < C; i++) {
            for(j = depth-2; j >= 0; j--) end[j] += end[j+1];
            if(i == 0) cout << end[0];
            else cout << " " << end[0];
        }
        cout << endl;
    }
    return 0;
}
