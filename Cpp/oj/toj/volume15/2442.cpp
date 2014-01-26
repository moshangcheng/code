#include <iostream>
using namespace std;

int cut(int n, int b)
{  
    while(n % b == 0) n /= b;
    return n;
}

int cpt(int n, int b)
{ 
    int num = 0;
    for(int i = n; i > 1; i /= b, num += i);
    return num;
}

int main()
{
    int i, j, n, m, n2, n5, n10, resA, resB;
    int vlu[4] = {6, 2, 4, 8};
    while(cin >> n >> m) {
        resA = resB = 1;
        n2 = cpt(n, 2) - cpt(m, 2) - cpt(n-m, 2);
        n5 = cpt(n, 5) - cpt(m, 5) - cpt(n-m, 5);   
        n10 = (n2 < n5) ? n2 : n5;
        n2 -= n10;  n5 -= n10;
        for(i = 1, j = n - m + 1; i <= m; i++, j++) {
            resA = (resA * cut( cut(j, 2), 5))%10;
            resB = (resB * cut( cut(i, 2), 5))%10;
        }
        if(n2 > 0) resA *= vlu[n2%4];
        else if(n5 > 0) resA *= 5; 
        if(resB == 3) resA *= 7;
        else if(resB == 7) resA *= 3;
        else if(resB == 9) resA *= 9; 
        cout << resA%10 << endl;          
    }
    return 0;
}
