#include <iostream>
using namespace std;

int main()
{
    bool div;
    int a[6], b[2][6] = {6, 4, 8, 8, 12, 8, 7, 3, 7, 7, 13, 7};
    int used[100];
    int i, j, sum, ntest = 0;
    while(1) {
        div = sum = 0;
        for(i = 0; i < 6; i++) {
            cin >> a[i];
            a[i] = a[i] > b[0][i] ? b[a[i]&1][i]: a[i];
            sum += (i+1)*a[i];
        }
        if(sum == 0) break;
        if(!(sum & 1) ) {
            sum /= 2;
            if(a[0] > 5) div = 1;
            else {
                memset(used, 0x7f, sizeof(used));
                for(j = 0; j <= a[0]; j++) used[j] = j;
                for(i = 1 ; i < 6; i++)
                for(j = 1; j <= sum; j++)
                if(used[j] <= a[i-1]) used[j] = 0;
                else if(j > i && used[j-i-1] < a[i]) 
                used[j] = used[j-i-1]+1;
                div = (used[sum] > a[5]) ? 0:1;
            }
        }
        cout << "Collection #" << ++ntest << ":\nCan";
        if(!div) cout << "'t" ;
        cout << " be divided.\n\n";
    }
    return 0;
}
