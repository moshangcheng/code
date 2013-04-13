#include <vector>
#include <iostream>
using namespace std;

const int MAX = 10000;

struct NODE { int data, prev, num; }T;

bool vst[MAX+1];
double sum,r[101];
int i, j, n, R[101];
vector<NODE >  L;

int main(){
    while (cin >> n && n > 0) {
        L.clear();
        sum = 0;
        memset(vst, 0, sizeof(vst));
        for(i = 0; i < n; i++) {
            cin >> r[i];
            sum += r[i];
        }
        R[0] = 0;
        for (i = 1; i <= n; i++) R[i] = r[i-1]*2*MAX/sum;
        NODE TP = {0, -1, 0};
        L.push_back(TP);
        for (i = 1; i <= n; i++) {
            for (j = L.size() - 1; j >= 0; j--) {
                int tp = L[j].data + R[i];
                if(vst[tp] || tp > MAX) continue;
                NODE TP = {tp, j, i};
                L.push_back(TP);
                vst[tp] = 1;
            }
        }
        
        int maxi = 0;
        for(i = 1; i < L.size(); i++) 
        if( L[i].data > L[maxi].data) maxi = i;
        while(1) {
            cout << L[maxi].num;
            maxi = L[maxi].prev;
            if(maxi > 0) cout << " ";
            else break;
        }           
        cout << endl;
    }
   return 0;
}
