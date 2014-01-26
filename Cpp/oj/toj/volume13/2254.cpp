#include <iostream>
using namespace std;

int main()
{
    char c;
    int i, j, n, a, b, maxn, minn, ntest;
    int letter[1001];
    cin >> ntest;
    while(ntest-- > 0)  {
        cin >> n;
        minn = 1001;   maxn = -1;
        memset(letter, 0, sizeof(letter));
        for(i = 0; i < n; i++) {
            cin >> c >> a >> b;
            if(a < minn) minn = a;
            if(b > maxn) maxn = b;
            for(j = a; j < b; j++) letter[j] ++;
        }
        for(i = minn; i < maxn; i++) 
        if(letter[i] > 0) cout << (char)(letter[i] + 'A' - 1);
        cout << endl;
    }
    return 0;
}
