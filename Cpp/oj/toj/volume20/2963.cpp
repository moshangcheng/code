#include <iostream>
using namespace std;

int s1, s2, N, T, FIND;
int  order[500], mnt[500];
struct bk{ int t, i; } rest[500];

void inline swap(int& a, int& b)
{
    int temp = a;
    a = b;
    b= temp;
}

void cpt(int d)
{
    if(d == N) {
        FIND = 1;
        return ;
    }
    if(s1 + rest[d].t <= T) {
        mnt[d] = s1;
        s1 += rest[d].t;
        cpt(d+1);
        if(FIND) return;
        s1 -= rest[d].t;
    }
    if(s2 + rest[d].t <= T) {
        mnt[d] = s2;
        s2 += rest[d].t;
        cpt(d+1);
        if(FIND) return;
        s2 -= rest[d].t;
    }
}

int main()
{
    int i, j;
    while(cin >> T >> N)  {
        for(i = 0; i < N; i++) {
            cin >> rest[i].t;
            rest[i].i = i;
            order[i] = i;
        }
        for(i = 0; i < N; i++)
        for(j = 1; j < N-i; j++) 
            if(rest[j].t < rest[j-1].t) {
                swap(rest[j].t, rest[j-1].t);
                swap(order[rest[j].i], order[rest[j-1].i]);   
                swap(rest[j].i, rest[j-1].i);
        }
        FIND = s1 = s2 = 0;
        cpt(0);
        if(FIND) {
            for(i = 0; i < N-1; i++) cout << mnt[order[i]] << " ";
            cout << mnt[order[N-1]] << endl;
        }
    }
    return 0;
}
        
        
