#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

const int MAX = 100000;
vector<int>  prime;
vector<pair<int, int> > L;

int main()
{
    int i, j, bound;
    prime.push_back(2);
    for(i = 3;i <= MAX; i++) {
        bound = floor(sqrt(i));
        for(j = 0; prime[j] <= bound; j++) if(i % prime[j] == 0) break;
        if(prime[j] > bound) prime.push_back(i);
    }
    
    int N, B, TN, TB, num;
    while(cin >> N >> B) {
        if(N == 0 && B == 0) break;
        TB = B;   L.clear();
        for(i = 0; TB > 1; i++) {
            if(TB % prime[i] != 0) {
                if(prime[i] > floor(sqrt(TB))) {
                    L.push_back( make_pair(TB, 1) );
                    break;
                }
                else continue;
            }
            for(j = 0; TB % prime[i] == 0; j++) TB /= prime[i];
            L.push_back( make_pair(prime[i], j) );
        }
        for(i = 0; i < L.size(); i++) {
            for(TN = N, j = 0; TN > 1; TN /= L[i].first, j += TN);
            if(i == 0) num = j/L[i].second;
            else if(num >= (j/L[i].second)) num = j/L[i].second;
        }
        cout << num << endl;
    }
    return 0;
}
        
            
            
            
            
        
    
    
