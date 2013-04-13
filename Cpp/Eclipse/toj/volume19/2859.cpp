#include <iostream>
using namespace std;

int main()
{
    int n, num, first, second, finds;
    while(cin >> n && n > 0) {
        finds = 0;
        cin >> num ;
        first = num ;
        for(int i = 1 ; i< n ; i++ ) {
            cin >> num;
            if( num == first ) continue;
            if(num > first) {
                second = first;
                first = num ;
            }
            else if(finds == 0 || num > second) second = num;
            finds = 1;
        }
        cout << second << endl;
    }
    return 0;
}
        
            
            
            
