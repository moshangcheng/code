// modify precision
#include <iostream>
#include <iomanip>
using namespace std;

int main () {
    double f = 113.1415926;
    //cout.setf(ios::floatfield);            // floatfield not set
    //cout.precision(5);
    cout << f << endl;
    cout << setw(8) << f << endl;
    cout.precision(10);
    cout << f << endl;
    cout.setf(ios::fixed,ios::floatfield);   // floatfield set to fixed
    cout << f << endl;
    system("pause");
    return 0;
}
