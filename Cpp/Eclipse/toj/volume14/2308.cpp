#include <iostream>
#include <cmath>
using namespace std;

unsigned num(unsigned n, unsigned b)
{
    unsigned sum = 0;
    for(; n > 1; n /= b, sum += n);
    return sum;
}

int main()
{
    unsigned i, j, k, bound, n, tp, prime[100];
    prime[0] = 2;   k = 1;
    for(i = 3;i < 450; i++) {
        bound = floor(sqrt(i));
        for(j = 0; prime[j] <= bound; j++) if(i % prime[j] == 0) break;
        if(prime[j] > bound) prime[k++] = i;
    }
    
    long long vlu;
    while(cin >> n >> k) {
        vlu = 1;
        for(i = 0; prime[i] <= n; i++) 
        vlu *= (1 + num(n, prime[i]) - num(k, prime[i]) - num(n-k, prime[i]));
        cout << vlu << endl;
    }
    return 0;
}
        
            
    
    
