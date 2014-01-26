#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

struct STREET { int n; double p; };
vector<STREET> S[100];

int main()
{
    STREET tp;
    bool vst[100];
    double maxp, pct, p[100];
    int np, ns, i, maxi, v1, v2;
    while(cin >> np && np > 0) {
        cin >> ns;
        for(i = 0; i < np; i++) S[i].clear();
        for(i = 0; i < ns; i++) {
            cin >> v1 >> v2 >> pct;
            v1 --;  v2 --;  pct/= 100.0;
            tp.n = v1;  tp.p = pct;
            S[v2].push_back(tp);
            tp.n = v2;
            S[v1].push_back(tp);
        }
        memset(vst, 0, sizeof(vst));
        for(i = 0; i < np; i++) p[i] = 0.0;
        p[0] = 1.0;
        while(1) {
            maxi = -1, maxp = 0.0;
            for(i = 0; i < np; i++)
            if(vst[i] == 0 && p[i] > maxp) {
                maxp = p[i];
                maxi = i;
            }
            if(maxi == -1 || maxi == np-1) break;
            vst[maxi] = 1;
            for(i = 0; i < S[maxi].size(); i++)
            if(vst[ S[maxi][i].n ] == 0)
            p[ S[maxi][i].n ] >?= maxp*S[maxi][i].p;
        }
        cout.setf(ios::fixed);
        cout << setprecision(6) << 100.0*maxp << " percent\n";
    }
    return 0;
}            
        
            
