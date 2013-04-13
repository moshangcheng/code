/**
 * @author moshangcheng
 * @version 1.0
 * @date 2011-4-15 下午07:48:56
 * @brief 筛法 素数 欧拉函数 约数 数论
 * @details http://hi.baidu.com/cjhh314/blog/item/bfe13bce20fb7c3db600c85c.html
 */
#include <iostream>
using namespace std;

const int MAX = 10000000;
bool notp[MAX];//素数判定
int pr[800000], phi[MAX];//pr存放素数,phi为欧拉函数,pn当前素数个数。

int main()
{
    int i, j, pn;
    pn = 0;
    phi[1] = 1;
    memset(notp, 0, sizeof(notp) );
    for(pn = 0, i = 2; i < MAX; i++)   {
        if(!notp[i]) {
            phi[i] = i-1;
            pr[pn++] = i;
        }
        for(j = 0; j < pn && pr[j] * i < MAX; j++) {
            notp[pr[j] * i] = 1;
            if(i % pr[j] == 0) {
                phi[i*pr[j]] = phi[i]*pr[j];
                break;
            }
            else phi[pr[j]*i] = phi[i]*(pr[j]-1);
        }
    }
    cout << pn << endl;
    return 0;
}
