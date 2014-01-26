#include <iostream>
using namespace std;

int main()
{
    bool matrix[100][100];
    int i, j, size, num_c, num_r, col, row, sum_r[100], sum_c[100];
    while(cin >> size && size > 0)  {
        num_c = num_r = 0;
        memset(sum_r, 0, sizeof(sum_r));
        memset(sum_c, 0, sizeof(sum_c));
        for(i = 0; i < size; i++)   {
            for(j = 0; j < size; j++) {
                cin >> matrix[i][j];
                sum_r[i] += matrix[i][j];
                sum_c[j] += matrix[i][j];
            }
        }
        for(i = 0; i < size; i++)   {
            if(sum_r[i]&1) {
                row = i;
                num_r++;
            }
            if(sum_c[i]&1) {
                col = i;
                num_c++;
            }
        }
        if(num_r > 1 || num_c > 1) cout << "Corrupt\n";
        else if(num_r == 0 && num_c == 0) cout << "OK\n";
        else if(num_r == 1 && num_c == 1)
        cout << "Change bit (" << row+1 << "," << col+1 << ")\n";
    }
    return 0;
}
        
        
