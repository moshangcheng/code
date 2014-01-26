#include <iostream>
using namespace std;

int size, num, sum;
int table[4][4];

bool place(int l, int r)
{
    bool t = 1;
    for(int i = 0; i < l; i++) 
    if(table[i][r] == -1)  t = 0;
    else if(table[i][r] == 1) t = 1;
    if(t)  for(int j = 0; j < r; j++) 
    if(table[l][j] == -1) t=0;
    else if(table[l][j] == 1) t = 1;
    if(t) return 1;
    return 0;      
}

void compute(int m)
{
    if(m < size*size) {
        int l = m / size;
        int r = m - size*l;
        if(table[l][r] == 0 && place(l,r)) {
            table[l][r] = -1;
            num ++;
            compute(m+1);
            num --;
            table[l][r] = 0;
        }
        if(size*size- m - 1 + num > sum) compute(m+1);
    }
    else if(num > sum) sum = num;
}
    
int main()
{
    char flag;
    while(cin >> size && size != 0)  {
        sum = num =0;
        for(int i = 0; i < size; i++)
        for(int j = 0; j < size; j++) {
            cin >> flag;
            if(flag == '.') table[i][j] = 0;
            else table[i][j] = 1;
        }
        compute(0);
        cout << sum <<endl;
    }
    return 0;
}
