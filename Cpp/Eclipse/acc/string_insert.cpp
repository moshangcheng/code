//结论：insert()函数复杂度为 O(n-k), 线性复杂度
//而 append() 和 + 复杂度为O(1) 
#include <iostream>
#include <string>
#include <ctime>
#include <iomanip>
using namespace std;

const unsigned MAX =500000;

int main()
{
    string s;
    double seconds;
    clock_t start, end;
    
    /*start = clock();
    for(int i = 0; i < MAX; i++) {
        for(int j = 0; j < 26; j++) s.insert(0,1, (char)(j+'a'));
    }
    end  = clock();
    seconds = (end - start)/1.0/CLK_TCK;
    cout.setf(ios::fixed);
    cout << "Using insert() : " << setprecision(15)  << seconds << endl;
    */
    s.erase();
    start = clock();
    for(int i = 0; i < MAX; i++) {
        for(int j = 0; j < 26; j++) s.append(1, (char)(j+'a'));
    }
    end  = clock();
    seconds = (end - start)/1.0/CLK_TCK;
    cout << "Using append() : " << seconds << endl;
    
    s.erase();
    start = clock();
    for(int i = 0; i < MAX; i++) {
        for(int j = 0; j < 26; j++) s += (char)(j+'a');
    }
    end  = clock();
    seconds = (end - start)/1.0/CLK_TCK;
    cout << "Using + : " << seconds << endl;
    system("pause");
    return 0;
}
