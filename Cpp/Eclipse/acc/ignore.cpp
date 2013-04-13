#include <iostream>
using namespace std;

int main()
{
    int x, y;
    cout << "Please input (x,y):\n";
    cin.ignore();
    cin >> x;
    cin.ignore();
    cin >> y;
    cin.ignore();
    cout << "Your input is: " << "(" << x << "," << y << ")" << endl;
    
    cout << "Please input real number: \n";
    cin >> x;
    cin.ignore();
    cin >> y;
    cout << "Your input is: " << x << "." << y << endl;
    system("pause");
    return 0;
}
