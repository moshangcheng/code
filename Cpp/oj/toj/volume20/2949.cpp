#include <iostream>
#include <string>
using namespace std;

int vlu[300][300];

bool isKiller(int ai, int aj, int d)
{
    bool k = 1;
    int i, j, m = (d+1)/2;
    for(i = 0; k && i <= d; i++)
    for(j = 0; k && j <= m; j++) 
    if(vlu[ai+i][aj+j] != vlu[ai+d-i][aj+d-j]) k = 0;
    if(k) return 0;
    else return 1;
}

int main()
{
    string s;
    int row, col, i, j, maxsize , flag;
    while(cin >> row >> col) {
        for(i = 0; i < row; i++)  {
            cin >> s;
            for(j = 0; j < col; j++)  vlu[i][j] = s[j] - '0';
        }
        maxsize = (row < col) ? row : col - 1;
        flag = 1;
        for(; maxsize > 0; maxsize--) {
            for(i = 0; flag && i + maxsize < row; i++)
            for(j = 0; flag && j + maxsize < col; j++)
            flag = isKiller(i, j, maxsize);
            if(!flag) break;
        }
        if(maxsize == 0) cout << -1 << endl;
        else cout << maxsize + 1 << endl;
    }
    return 0;
}
        
        
        
