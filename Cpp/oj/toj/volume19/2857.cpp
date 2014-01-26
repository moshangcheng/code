#include <iostream>
#include <algorithm>
using namespace std;

int f(int m)
{
    int i, j, tp, a[6];
    for(i = 0; m > 0; m = m / 10, i++) {
        tp = m % 10;
        for(j = i; j > 0; j--) 
        if(tp < a[j-1]) a[j] = a[j-1];
        else break;
        a[j] = tp;
    } 
    for(j = 0, tp = 0; j < i; j++) tp = tp*10 + a[j];
    return tp;    
}

int main()
{
    int N, x, m, t;
    while(cin >> N && N > 0) {
        for(int i = 0; i < N; i++) {
            cin >> x;
            t = f(x);
            if(i == 0) m = t;
            else m = (m < t)? t : m;
        }
        cout << m << endl;
    }
    return 0;
}
            
    
