#include <iostream>
using namespace std;

int gcd(int a, int b)
{
    int c;
    while(a != 0) {
        c = b % a;
        b = a;
        a = c;
    }
    return b;
}

int main()
{
    int N, W, cpt[100], i, go, a;
    while(cin >> N >> W) {
        if(N == 0 && W == 0) break;
        for(go = i = 0; i < N; i++) {
            cin >> cpt[i];
            if(cpt[i] >= W) go = 1;
        }
        for(i = 1, a = cpt[0]; i < N; i++) a = gcd(a, cpt[i]);
        if(go && W % a == 0) cout << "YES\n";
        else cout << "NO\n";
    }
    return 0;
}
        
