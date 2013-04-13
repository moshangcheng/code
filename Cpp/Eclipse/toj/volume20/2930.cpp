#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;

const int MAX = 10001;
bool vst[MAX];
long long sum;
int n, num[MAX];
vector<pair<int,int> > p[MAX];

void dfs(int point, int prt)
{
    num[point]++;
    for(int i = 0; i < p[point].size(); i++)  {
        pair<int,int> temp = p[point][i];
        if(temp.first != prt)  {
            dfs(temp.first, point);
            num[point] += num[ temp.first ];
            sum += (long long)temp.second * num[temp.first] * (n - num[temp.first]);
        }
    }
}

int main()
{
    int t, a, b, d;
    cin >> t;
    while(t-- > 0) {
        cin >> n;
        for(int i = 0; i < n; i++) p[i].clear();
        for(int i = 0; i < n-1; i++) {
            cin >> a >> b >> d;
            p[a].push_back( make_pair(b, d) );
            p[b].push_back( make_pair(a, d) );
        }
        sum = 0;
        memset(num, 0, sizeof(num));
        dfs(0, 0);
        cout.setf(ios::fixed);
        cout << setprecision(10) << sum * 2.0 / n / (n-1) <<endl;
    }
    return 0;
}
        
        
