#include <iostream>
#include <map>
using namespace std;

int main()
{
    map<int,int> int_m, int_n;
    map<int,int>::iterator cnt;
    for(int i = 0; i < 10; i++) {
        int_m.insert( pair<int,int>(i%7, i) );
        for(cnt = int_m.begin(); cnt != int_m.end(); cnt++) 
        cout << (*cnt).first << "," << (*cnt).second <<"  ";
        cout << endl << endl;
    }
    cout << endl << endl;
    
     for(int i = 0; i < 10; i++) {
        int_n[i%7] = i;
        for(cnt = int_n.begin(); cnt != int_n.end(); cnt++) 
        cout << (*cnt).first << "," << (*cnt).second <<"  ";
        cout << endl << endl;
    }
    system("pause");
    return 0;
}
