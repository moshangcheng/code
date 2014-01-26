#include <iostream>
#include <algorithm>
using namespace std;

int state[200];

int main()
{
    int i, sum, N;
    while(cin >> N && N > 0) {
        for(i = 0; i < N; i++) cin >> state[i];
        sort(state, state+N);
        for(sum = i = 0; i <= N/2; i++) sum += state[i]/2+1;
        cout << sum << endl;
    }
    return 0;
}
