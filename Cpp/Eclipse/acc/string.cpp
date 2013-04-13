#include <iostream>
#include <string>
using namespace std;

int main()
{
    string s1, s2;
    cin >> s1 >> s2;
    if( s1 == s2 ) cout << s1 << " = " << s2 << endl;
    else cout << s1 << " != " << s2 << endl;
    
    string s3 =  s1 + s2;
    cout << s3 << " = " << s1 << " + " << s2 << endl;
    
    string s4 = s3 + 'x';
    cout << s4 << " = " << s3 << " + " << 'x' << endl;
    
    string s5 = 'x' + s3;
    cout << s5 << " = " << 'x' << " + " << s3 << endl;
    
    system("pause");
    return 0;
}
