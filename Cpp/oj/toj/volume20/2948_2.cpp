#include <iostream>
#include <iomanip>
using namespace std;

bool vst[20];
int size, vlu[20][20];
double maxp,  maxs[20];

void p(int d, double cntp)
{
    if(d == size) {
        if(maxp < cntp) maxp = cntp;
        return;
    }
    if(cntp * maxs[d] < maxp) return;
    for(int i = 0; i < size; i++) {
        if(vst[i]) {
            vst[i] = 0;
            p(d+1, cntp*vlu[d][i]/100.0);
            vst[i] = 1;
        }
    }
}

int main()
{
    int i, j;
    while(cin >> size) {
        maxp = 0;
        for(i = 0; i < size; i++)
        for(j = 0; j < size; j++)  cin >> vlu[i][j];
        for(i = size - 1; i >= 0; i--) {
            maxs[i] = vlu[i][0];
            for(j = 1; j < size; j++) 
            if(maxs[i] < vlu[i][j])  maxs[i] = vlu[i][j];
            if(i < size - 1) maxs[i] *= maxs[i+1]/100.0;
            else maxs[i] /= 100.0;
        }
        memset(vst, 1, sizeof(vst));
        p(0, 1);    
        cout.setf(ios::fixed);
        cout << setprecision(8) << 100*maxp << endl;
    }
    return 0;
}
