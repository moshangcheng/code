#include <iostream>
using namespace std;

unsigned vlu[10000][3], s_cnt[3], s_prev[3];

inline unsigned max(unsigned a, unsigned b)
{ return (a > b)? a: b; }

int main()
{
    int i, j, ntest, ncave;
    cin >> ntest;
    while(ntest-- > 0) {
        cin >> ncave;
        for(i = 0; i < ncave; i++) 
        cin >> vlu[i][0] >> vlu[i][1] >> vlu[i][2];
        s_prev[0] = s_prev[1] = s_prev[2] = 0;
        for(i = 0; i < ncave; i++) {
            s_cnt[0] = max(s_prev[1], s_prev[2]) + vlu[i][0];
            s_cnt[1] = max(s_prev[2], s_prev[0]) + vlu[i][1];
            s_cnt[2] = max(s_prev[0], s_prev[1]) + vlu[i][2];
            s_prev[0] = s_cnt[0];
            s_prev[1] = s_cnt[1];
            s_prev[2] = s_cnt[2];
        }
        cout << max(s_cnt[0], max(s_cnt[1], s_cnt[2])) << endl;
    }
    return 0;
}
            
               
        
        
        
        
