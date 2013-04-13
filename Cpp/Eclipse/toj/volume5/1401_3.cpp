#include <iostream>
using namespace std;

int main()
{
    int i, j;
    string l, r;
    while(cin >> l >> r) {
        for(i = 0, j = 0; r[i] != '\0' && l[j] != '\0'; i++) 
        if(r[i] == l[j]) j++;
        if(l[j] == '\0') cout << "Yes\n";
        else cout << "No\n";
    }
    return 0;
}
        
    
