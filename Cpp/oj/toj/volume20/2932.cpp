#include <string>
#include <iostream>
using namespace std;

int main()
{
    string s;
    int wdlen[11];
    long long sum[51];
    int i, j, k, ntest, nword, num, len, ncase;
    cin >> ntest;
    while(ntest-- > 0)  {
        cin >> nword >> num >> ncase;
        memset(wdlen, 0, sizeof(wdlen));
        for(i = 0; i < nword; i++) {
            cin >> s;
            wdlen[s.size()] ++;
        }
        while(ncase-- > 0)  {
            cin >> len;
            memset(sum, 0, sizeof(sum));
            for(i = 3; i < 11; i++) sum[i] = wdlen[i];
            for(i = 1; i < num; i++) 
            for(j = len; j > 0; j--) {
                for(k = 3; k < 11 && k + j <= len; k++)  
                sum[k+j] += wdlen[k]*sum[j];
                sum[j] = 0;
            }
            cout << sum[len] << endl;
        }
    }
    return 0;
}
            
            
            
        
