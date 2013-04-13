#include <iostream>
#include <algorithm>
#include <iterator>
using namespace std;

int main()
{
    int A[] = {1, 2, 3, 4, 5, 6};
    const int N = sizeof(A) / sizeof(int);

    make_heap(A, A+N);
    cout << "Before pop: ";
    copy(A, A+N, ostream_iterator<int>(cout, " "));

    pop_heap(A, A+N);
    cout << endl << "After pop: ";
    copy(A, A+N-1, ostream_iterator<int>(cout, " "));
    cout << endl << "A[N-1] = " << A[N-1] << endl;
    
    system("pause");
    return 0;
}

