//即求与[m，n] > 1 且 [m, n] > n 且小于 n的数的个数
// n+1 - (1+t1)(1+t2)...(1+tk) - f(n)
// f(n)为欧拉函数，与n互质的数的个数，减掉一个重复的1
// n = (p1^t1)*(p2^t2)*...(pk^tk) 
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

const unsigned MAX = 1<<16;

int main()
{
    unsigned i, j, k, bound;
    vector<unsigned> prime;
    prime.push_back(2);
    for(i = 3;i < MAX; i++) {
        bound = floor(sqrt(i));
        for(j = 0; prime[j] <= bound; j++) if(i % prime[j] == 0) break;
        if(prime[j] > bound) prime.push_back(i);
    }
    
    unsigned p, f, sum, n;
    while(cin >> n && n > 0)    {
        sum = n+1;
        for(f = p = 1, i = 0; n > 1; i++) {
            k = prime[i];
            if(n % k == 0) {
                for(n /= k, p *= k-1, j = 1; n % k == 0; j++, n /= k) 
                p *= k;
                f *= j + 1;            
            }
            else  if(k > sqrt(n)) {
                f *= 2;
                p *= n - 1;
                break;
            }
        }       
        sum -= p + f;     
        cout << sum << endl;
    }
    return 0;    
}
