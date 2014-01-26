#include <iostream>
using namespace std;

const int MAX = 1<<16;
bool notp[MAX];//素数判定
int pr[8000], phi[MAX], divnum[MAX], e[MAX];
//pr存放素数,phi为欧拉函数,pn当前素数个数。

int main()
{
    int i, j, k, pn;
    pn = 0;
    e[1] = divnum[1] = phi[1] = 1;
    memset(notp, 0, sizeof(notp) );
    for(pn = 0, i = 2; i < MAX; i++)   {
        if(!notp[i]) {
            phi[i] = i-1;
            pr[pn++] = i;
            divnum[i] = 2;
            e[i] = 1;
        }
        for(j = 0; j < pn && pr[j] * i < MAX; j++) {
            k = pr[j] * i;
            notp[k] = 1;
            if(i % pr[j] == 0) {
                e[k] = e[i] + 1;
                phi[k] = phi[i] * pr[j];
                divnum[k] = divnum[i]/(e[i]+1) * (e[i]+2);
                break;
            }
            else {
                e[k] = 1;
                phi[k] = phi[i] * (pr[j]-1);
                divnum[k] = divnum[i] * 2;
            }
        }
    }
    cout << pn << endl;
    system("pause");
    return 0;
}
