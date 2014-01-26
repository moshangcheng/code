#include <iostream>
#include <iomanip>
using namespace std;

int prt[20][20];
bool vst[20][20];
double p[20][20], poss[20][20][20];

bool path(int i, int j, int k)
{
    for(;i > 0 && prt[i][j] != k; i--) j = prt[i][j];
    if(i > 0) return 0;
    else return 1;
}

int main()
{
    double maxp;
    int maxi, maxj;
    int i, j, k, tp, size;
    while(cin >> size)  {
        for(i = 0; i < size; i++) 
        for(j = 0; j < size; j++) {
            cin >> tp;
            if(i == 0) {
                p[i][j] = tp/100.0;
                continue;
            }
            p[i][j] = 0.0;
            for(k = 0; k < size; k++) {
                if(k == j) poss[i-1][k][j] = 0.0;
                else poss[i-1][k][j] = tp/100.0;
            }
        }
        for(i = 0; i < size; i++) prt[0][i] = -1;
        memset(vst, 1, sizeof(vst));
        while(1) {
            maxp = 0;
            for(i = 0; i < size; i++)
            for(j = 0; j < size; j++)
            if(vst[i][j] && p[i][j] >= maxp) {
                maxp = p[i][j];
                maxi = i;   maxj = j;
            }
            if(maxi == size - 1) break;
            vst[maxi][maxj] = 0;
            for(k = 0; k < size; k++) {
                if(poss[maxi][maxj][k] * maxp > p[maxi + 1][k]) {
                    if(path(maxi, maxj, k)) {
                        p[maxi + 1][k] = maxp * poss[maxi][maxj][k];
                        prt[maxi + 1][k] = maxj;
                    }
                }
            }
        }
        cout.setf(ios::fixed);
        cout << setprecision(8) << 100*maxp << endl;
    }
    return 0;
}
                
                
                
                
                
                
                
                
                
        
