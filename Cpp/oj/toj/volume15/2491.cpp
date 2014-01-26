#include <iostream>
#include <string>
using namespace std;
    
int main()
{
    int times, i, j;
    string s, tp;
    while(cin >> s && s != ".") {
        cin >> times;
        tp = s;
        do {
            for(j = 0; j <times; j++) cout << tp;
            cout << endl;
            char c = tp[0];
            tp.append(1, c).erase(0, 1);
        }while(tp != s);
    }
    return 0;
}
            
