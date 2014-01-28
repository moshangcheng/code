#include <iostream>
#include <string>
#include <ctime>
#include <iomanip>
using namespace std;

const unsigned MAX =1000000;

int main()
{
    string s="abcdefghijklmnopqrstuvwxyz";
    double seconds;
    clock_t start, end;
    
    start = clock();
    for(int i = 0; i < MAX; i++)
    for(int j = 0; j < 26; j++) s[j] = 'c';
    end  = clock();
    seconds = (end - start)/1.0/CLK_TCK;
    cout.setf(ios::fixed);
    cout << setprecision(10)  << seconds << endl;
    
    /*s.erase();
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
    cout << "Using + : " << seconds << endl;*/
    
    system("pause");
    return 0;
}
