#include <iostream>
using namespace std;

int main()
{
    int N, r, i, t;
    while(cin >> N) {
        for(i = 1,t = 1, r = 0; (r = (r + t)%N) != 0; i++) t = t*10%N;
        cout << i <<endl;
    }
    return 0;
}
            
            
        
