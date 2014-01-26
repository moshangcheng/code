#include <iostream>
#include <cmath>
using namespace std;

int main()
{    
    int i, j, k, N, B, maxp, np, p, num;
    while(cin >> N >> B) {
        if(N == 0 && B == 0) break;
        for(p = maxp = 0, i = 2; B > 1; i++) {
            if(B % i != 0) {
                if(i > floor(sqrt(B))) {
                    if(maxp < B) {
                        maxp = B;
                        np = 1;
                        p = B;
                    }
                    break;
                }
                else continue;
            }
            for(k = 0, j = 1; B % i == 0; k++, j *= i) B /= i;
            if(maxp < j) {
                maxp = j;
                np = k;
                p = i;
            }          
        }
        for(j = 0; N > 1; N /= p, j += N);
        cout << j/np << endl;
    }
    return 0;
}
        
            
            
            
            
        
    
    
