#include <iostream>
#include <vector>
using namespace std;
 
int num[20][1000005];
vector<int> V[20];

int compute(int i, int j)
{
    if(num[i][j] > 0) return num[i][j];
    num[i][j] = 1;
    if(j > 0) {
        for(int k = 0; k < V[i].size(); k++)
        num[i][j] += compute(V[i][k], j-1);
        num[i][j]%= 2007;
    }
    return num[i][j];
}

int main()
{
    int N, M, T, v1, v2;
    while(cin >> N >> M) {
        if(N == 0 && M == 0) break;
        for(int i = 0; i < N; i++) {
            V[i].clear();
            V[i].push_back(i);
        }
        memset(num, 0, sizeof(num));
        for(int i = 0; i < M; i++) {
            cin >> v1 >> v2;
            v1--;  v2--;
            V[v1].push_back(v2);    V[v2].push_back(v1);
        }
        cin >> T;
        cout << compute(0, T) << endl;
    }
    return 0;
}
        
