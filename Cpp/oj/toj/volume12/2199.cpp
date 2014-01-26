#include <iostream>
#include <algorithm>
using namespace std;

int a[1000], N;

bool find(int vlu)
{
    int begin = 0, end = N - 1, mid;
    while(begin <= end) {
        mid = (begin + end)/2;
        if(vlu == a[mid]) break;
        else if(vlu < a[mid]) end = mid - 1;
        else if(vlu > a[mid]) begin = mid + 1;
    }
    if(vlu == a[mid]) return 1;
    else return 0;
}

int main()
{
    int i, j, T;
    while(cin >> N && N > 0) {
        T = -1;
        for(i = 0; i < N; i++) cin >> a[i];
        sort(a, a + N);
        for(i = N - 2; i > 0; i--)
        for(j = i - 1; j >= 0; j--)
        if(find(a[i] + a[j]) && (a[i] + a[j] > T))
        T = a[i] + a[j];
        cout << T << endl;
    }
    return 0;
}
        
