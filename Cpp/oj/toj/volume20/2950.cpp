#include <iostream>
using namespace std;

int main()
{
    int i, j, sum, res, vlu[9];
    while(cin >> vlu[0]) {
        sum = 0;
        for(i = 1; i < 9; i++) cin >> vlu[i];
        for(i = 0; i < 9; i++) sum += vlu[i];
        res = sum - 100;
        for(i = 0;i < 9; i++) {
            for(j = i + 1; j < 9; j++)
            if(vlu[i] + vlu[j] == res) break;
            if(j < 9) break;
        }
        for(int k = 0; k < 9; k++) 
        if(k != i && k != j) cout << vlu[k] << endl;
    }
    return 0;
}
        
