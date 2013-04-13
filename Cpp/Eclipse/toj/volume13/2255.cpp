#include <iostream>
#include <string>
using namespace std;

int c[2][26] = {2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5, 5, 
                6, 6, 6, 7, 7, 7, 7, 8, 8, 8, 9, 9, 9, 9,
                1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3,
                1, 2, 3, 1, 2, 3, 4, 1, 2, 3, 1, 2, 3, 4};
int inline convert(char ch, int& nb)
{
    if(ch == ' ') {
        nb = 1;
        return 1;
    }
    nb = c[1][ch - 'A'];
    return c[0][ch - 'A'];
}

int main()
{
    string s;
    int p, w, i, n, sum, prev, cnt, ntest;
    cin >> ntest;
    while(cin >> p >> w) {
        getline(cin, s);
        getline(cin, s);
        prev = convert(s[0], n);
        for(sum = p * n, i = 1; i < s.size(); i++) {
            cnt = convert(s[i], n);
            if(cnt == prev && prev != 1) sum += w + n * p;
            else {
                sum += p * n;
                prev = cnt;
            }
        }
        cout << sum << endl;
    }
    return 0;
}
            
            
            
            
