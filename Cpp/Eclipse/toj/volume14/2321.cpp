#include <iostream>
#include <iomanip>
#include <list>
using namespace std;

int len(int n)
{
    int i, j;
    for(j=0, i = 1; i <= n; j++, i *= 10);
    return j;
}

int main()
{
    list<int> L;
    list<int>::iterator cnt;
    int i, j, k, tp, x1, x2, N;
    while(cin >> N) {
        L.clear();
        for(i = 1, k = 1; k <= N; i++, k *= 10) {
            x1 = N/(11*k);
            x2 = N%(11*k);
            for(j = (x1 > 0)? 0: 1 ; j < 10; j ++) {
                tp = x2 - j*k;
                if(tp < 0) break;
                if(tp >= 2*k || (tp & 1)) continue;
                tp /= 2;
                L.push_back(x1*10*k + j*k + tp);
            }
        }
        L.sort();
        L.unique();
        cout << L.size() << endl;
        for(cnt = L.begin(); cnt != L.end(); cnt++) {
            cout << *cnt << " + ";
            cout.width(len(*cnt)-1);
            cout.fill('0');
            cout << N - (*cnt) <<  " = " << N << endl;
        }
    }
    return 0;
}
                    
                    
                    
                    
                    
                    
                    
                    
                                         
