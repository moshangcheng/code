#include <iostream>
using namespace std;

const int MAX = 21;
const int LENGTH = 1<<19;
const int BOUND = 0x7f7f7f7f;
int vst[MAX], nmove[LENGTH], move[LENGTH][MAX];

bool dfs()  {
    int i, j, sum, m = 0;
    for(sum = 0, j = 2; j < MAX; j++)
        sum = 2*sum + (vst[j] == 0? 1:0);
    if(nmove[sum] != BOUND) return (nmove[sum] > 0);
    for(i = 2; i < MAX; i++) {
        if(vst[i] != 0) continue;
        vst[i] = i;
        for(j = 2; j < MAX; j++)
        if(vst[j] != 0 && i+j < MAX && vst[i+j] == 0) vst[i+j] = i;
        if(dfs() == 0) move[sum][m++] = i;
        for(j = 2; j < MAX; j++) if(vst[j] == i) vst[j] = 0;
    }
    nmove[sum] = m;
    return (m > 0);
}
    
int main()
{
    int i, j, k, s, n;
    int ntest, otest = 0;
    memset(vst, 0, sizeof(vst));
    memset(nmove, 0x7f, sizeof(nmove));
    dfs();
    cin >> ntest;
    while(otest++ < ntest)  {
        cin >> n;
        memset(vst, 0, sizeof(vst));
        for(i = 0; i < n; vst[k] = 1, i++) cin >> k;
        for(i = 2, s = 0; i < MAX; i++) 
            s = 2*s + (vst[i] == 1? 1:0);
        cout << "Scenario #" << otest << ":\n";
        if(nmove[s] == BOUND) cout << "impossible state.\n\n";
        else if(nmove[s] == 0) cout << "There is no winning move.\n\n";
        else {
            cout << "The winning moves are: " << move[s][0];
            for(i = 1; i < nmove[s]; i++) cout << " "<< move[s][i];
            cout << ".\n\n";
        }
    }
    return 0;
}
