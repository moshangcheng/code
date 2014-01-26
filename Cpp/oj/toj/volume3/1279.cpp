#include <iostream>
#include <algorithm>
using namespace std;

int main()
{
    int num_test, n, w, d[1000];
    cin >> num_test;
    while(num_test-- > 0) {
        cin >> n;
        w = 0;
        for(int i = 0; i < n; i++) cin >> d[i];
        sort(d, d + n);
        for(int i = n -1; i > -1; i--) 
        if( (n - i)*d[i] > w) w = (n - i)*d[i];
        cout << w << endl;
    }
    return 0;
}
        
    
