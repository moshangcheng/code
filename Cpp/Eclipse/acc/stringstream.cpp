#include <iostream>
#include <sstream>
#include <string>
using namespace std;

int main()
{
    int n;
    string s1;
    getline(cin, s1);
    
    istringstream stream2;
    stream2.str(s1);
    stream2 >> n;
    cout << n << endl;
    
    ostringstream stream1;
    stream1 << "Testing!" << s1 << endl;
    cout << stream1.str();
    
    system("pause");
    return 0;
}
