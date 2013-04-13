#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;

typedef long long ll;

ll S[10002];
pair<ll, ll> p[10002];

const ll Min = -1000000001; 
const ll Max =  1000000000;

bool operator < (pair<ll, ll> a, pair<ll, ll> b)
{ return a.first < b.first; }

int main()
{
    ll i, j, cost, prev, cnt, dist, s, N, M;
    while(cin >> N >> M) {
        for(i = 1; i <= N; i++) cin >> p[i].first >> p[i].second;
        p[0].first = Min;   p[0].second = 0;
        sort(p, p + N + 1);
        if(p[N].first < Max) {
            N++;
            p[N].first = Max;   p[N].second = 0;
        }
        for(S[0] = 0, i = 1; i <= N; i++)  S[0] += p[i].second;
        for(i = 1; i <= N; i++) S[i] = S[i-1] - 2*p[i].second;
        for(cost = 0, i = 1; i <= N; i++) 
            cost += (p[i].first - p[0].first)*p[i].second;
        s = 0;
        for(i = 0; i < N; i++) {
            cnt = p[i].first;
            if(S[i] == 0) {
                if(cost <=  M) s += p[i+1].first - cnt;
                continue;
            }
            dist = floor(1.0*(cost-M)/S[i]);
            if(dist < 0 && cost < M) 
                s += p[i+1].first - cnt;
            else if(dist == 0 && S[i] > 0) 
                s += p[i+1].first - cnt;
            else if(dist > 0) {
                if(dist + cnt > p[i+1].first && cost < M) 
                    s += p[i+1].first - cnt;
                else if(dist + cnt <= p[i+1].first) {
                    if(cost < M) s += dist;
                    else if(cost > M) 
                        s += p[i+1].first- cnt - dist;
                        if(dist*S[i] == cost-M) s++;
                }
            }
            cost -= S[i]*(p[i+1].first - cnt);
        }
        cout << s << endl;
    }
    return 0;
}
            
            
            
