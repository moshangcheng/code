#include <iostream>
#include <utility>
using namespace std;

int main()
{
    pair<int, double> a[3];
    for(int i = 0; i < 3; i++) a[i]= pair<int,double>(i, i+0.01);                      
    cout << a[0].first << " , " << a[0].second << endl;
    system("pause");
    return 0;
}


    
