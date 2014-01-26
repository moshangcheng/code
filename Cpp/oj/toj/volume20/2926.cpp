#include <iostream>
using namespace std;

int nprb, mnt, best;
int res[3], cost[3][10];

void cpt(int slv, int iprb)
{
    if(nprb - iprb + slv <= best) return;
    if(slv > best) best = slv;
    for(int i = 0; i < 3; i++) {
        if(res[i] >= cost[i][iprb]) {   
            res[i] -= cost[i][iprb];
            cpt(slv + 1, iprb + 1);
            res[i] += cost[i][iprb];
        }
        cpt(slv, iprb + 1);
    }
}    
    
int main()
{
    int i, j, ntest;
    cin >> ntest;
    while(ntest-- > 0)  {
        best = 0;
        cin >> nprb >> mnt;
        for(i = 0; i < 3; i++)  {
            res[i] = mnt;
            for(j = 0; j < nprb; j++) {
                cin >> cost[i][j];
                if(cost[i][j] < 0) cost[i][j] = mnt + 1;
            }
        }
        cpt(0, 0);
        cout << best << endl;
    }
    return 0;
}
        
        
        
        
