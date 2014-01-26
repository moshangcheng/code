#include <iostream>
#include <string>
using namespace std;

int main()
{
    int a, b, vlu[10][4] = {0, 0, 0, 0, 1, 1, 1, 1,
                            6, 2, 4, 8, 1, 3, 9, 7,
                            6, 4, 6, 4, 5, 5, 5, 5, 
                            6, 6, 6, 6, 1, 7, 9, 3,
                            6, 8, 4, 2, 1, 9, 1, 9};
    string n, m;
    while(cin >> n >> m && (n != "0" || m != "0"))  {
        if(m == "0" ) {
            cout << 1 << endl;
            continue;
        }
        a = n[n.size() - 1] - '0';
        b = m[m.size() - 1] - '0';
        if(m.size() > 1) b += (m[m.size() - 2] - '0')*10;
        b %= 4;
        cout << vlu[a][b] << endl;
    }
    return 0;
}
                
                
            
        
