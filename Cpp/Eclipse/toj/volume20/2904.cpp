#include<iostream>
using namespace std;

int main()
{
    long long c, sum, min, max;
    long long  a, b, num[10000];
    while(cin >> a >> b >> c) {
        for(int i = 0; i < c; i++) num[i] = (b - a + 1) / c;
        if((b - a + 1) % c != 0) {
            min = a % c;    max = b % c;
            if(max < min) {
                for(int i = 0; i <= max; i++) num[i] += 1;
                for(int j = min; j < c; j++)  num[j] +=1 ;
            }
            else for(int i = min; i <= max; i++) num[i] += 1;
        }
        
        sum = num[0] / 2;
        if(c % 2 == 0) sum += num[c/2] / 2;
        for(int i = 1; i < (c+1)/2; i++)
        sum += (num[i] < num[c-i]) ? num[i] : num[c-i];
        cout << sum << endl;
    }
    return 0;
}
        
        
        
        
        
    
