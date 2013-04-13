#include <iostream>
using namespace std;

int p[11], S[11][11], P[11][11];

void print(int i, int j)
{
    if(i == j) cout << "A" << i;
    else {
        cout << "(";
        print(i, P[i][j]);
        cout << " x "; 
        print(P[i][j] + 1, j);
        cout << ")";
    }
}

int main()
{
    int i, j, k, l, tp, ntest = 0, N;
    while(cin >> N && N > 0)  {
        memset(S, 0x7f, sizeof(S));
        for(i = 0; i < N; i++) cin >> p[i] >> p[i+1];
        for(l = 0; l < N; l++) {
            if(l == 0)  for(j = 1; j <= N; j++) S[j][j] = 0;
            else {
                for(i = 1; i + l <= N; i++) {
                    j = l + i;
                    for(k = i; k < j; k++) {
                        tp = S[i][k] + S[k+1][j] + p[i-1]*p[k]*p[j];
                        if(tp < S[i][j]) {
                            S[i][j] = tp;
                            P[i][j] = k;
                        }
                    }
                }
            }
        }
        cout << "Case " << ++ntest << ": ";
        print(1, N);
        cout << endl;
    }
    return 0;
}

        
        
        
