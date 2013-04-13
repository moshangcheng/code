#include <iostream>
#include <set>
using namespace std;

int main()
{
    int i;
    set<int> int_s;
    set<int>::iterator cnt, tcnt;
    //set<int>::reverse_iterator rcnt;
    for(i = 0; i < 10; i++) {
        int_s.insert(i%7);
        for(cnt = int_s.begin(); cnt != int_s.end(); cnt++) 
        cout << *cnt <<" ";
        cout << endl << endl;
    }
    //for(rcnt = int_s.rbegin(); rcnt != int_s.rend(); rcnt++)
    //    cout << *rcnt << " ";
    //cout << endl;
    for(cnt = int_s.begin(); cnt != int_s.end();) {
        tcnt = cnt++;
        int_s.erase(tcnt);
        for(tcnt = int_s.begin(); tcnt != int_s.end(); tcnt++) 
        cout << *tcnt <<" ";
        cout << endl << endl;
    }
    
    system("pause");
    return 0;
}
