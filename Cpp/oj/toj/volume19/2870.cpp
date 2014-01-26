#include <iostream>
#include <vector>
using namespace std;

struct edge { int i, d; };
int d[200];
bool vst[200];
vector<edge> C[200];

int main()
{
    edge t;
    int N, M, i, j, v1, v2, dist, end, mind, minp;
    while(cin >> N && N > 0) {
        cin >> M;
        for(i = 0; i < N; i++) C[i].clear();
        for(i = 0; i < M; i++) {
            cin >> v1 >> v2 >> dist;
            t.i = v2; t.d = dist;
            C[v1].push_back(t);
            t.i = v1;
            C[v2].push_back(t);
        }
        cin >> end;
        memset(d, 0x7f, sizeof(d));
        memset(vst, 1, sizeof(vst));
        d[0] = 0;
        for(i = 0; i <= end; i++) {
            minp = -1, mind = 0x7f7f7f7f;
            for(j = 0; j < N; j++)
            if(vst[j] && mind > d[j]) {
                minp = j;
                mind= d[j];
            }
            vst[minp] = 0;
            for(j = 0; j < C[minp].size(); j++)
            if(vst[ C[minp][j].i ] )
            d[ C[minp][j].i ] <?= mind + C[minp][j].d;
        }
        cout << minp << endl;
    }
    return 0;
}
            
        
            
            
            
