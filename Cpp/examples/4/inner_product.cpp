#include <iostream>
#include <numeric>
using namespace std;

int main()
{
    int A1[] = {1, 2, 3};
    int A2[] = {4, 1, -2};
    const int N1 = sizeof(A1) / sizeof(int);
    
    cout << "The inner product of A1 and A2 is " 
       << inner_product(A1, A1 + N1, A2, 2)
       << endl;
    system("pause");
    return 0;
}

