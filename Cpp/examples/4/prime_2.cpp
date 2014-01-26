//利用了每个合数必有一个最小素因子。
//每个合数仅被它的最小素因子筛去正好一次。所以为线性时间。
//代码中体现在：
//if(i%pr[j]==0)break;
//pr数组中的素数是递增的,当i能整除pr[j]，
//那么i*pr[j+1]这个合数肯定被pr[j]乘以某个数筛掉。
//因为i中含有pr[j],pr[j]比pr[j+1]小。接下去的素数同理。
//所以不用筛下去了。
//满足i%pr[j]==0这个条件之前以及第一次满足改条件时,
//pr[j]必定是pr[j]*i的最小因子。
#include <iostream>
using namespace std;

const int MAX = 1000000;
bool notp[MAX];//素数判定
int pr[670000];//pr存放素数,pn当前素数个数。

int main()
{
    int i, j, pn;
    pn = 0;
    memset(notp, 0, sizeof(notp) );
    for(pn = 0, i = 2; i < MAX; i++)   {
        if(!notp[i]) pr[pn++] = i;
        for(j = 0; j < pn && pr[j] * i < MAX; j++) {
            notp[pr[j] * i] = 1;
            if(i % pr[j] == 0) break;
        }
    }
    cout << pn << endl;
    system("pause");
    return 0;
}
