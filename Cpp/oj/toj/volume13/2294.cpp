#include <iostream>
using namespace std;

unsigned f(unsigned n)
{
    unsigned sum = 0;
    for(; n > 0; n /= 10) if(n % 10 == 0) sum ++;
    return sum;
}

unsigned num(unsigned n)
{
    unsigned sum = 1, T = 1;
    while(n > 0)   {
        //三部分，一部分是 1015 ,必须考虑 1011 ~1015 含有的0 
        //因为取整后 1011～1015会丢失，
        //乘以 T 是因为 10100 ~ 10109也丢失了 
        //一部分是 1010 等末尾为0的数字含有的0
        //一部分是 1010 变成 101 后 1000 ~ 1009，
        //900 ~ 909，...，100~109等数字的 0
        // 因为要考虑 101， 所以 T 减掉 1              
        sum += f(n)*(n%10)*T + n/10 + (n-1)/10*(T-1);
        n /= 10; 
        T *= 10;
    }
    return sum;
}

int main()
{
    unsigned m, n;
    while(cin >> m >> n) {
        if(m == 0) cout << num(n) << endl;
        else cout << num(n) - num(m-1) << endl;
    }
    return 0;
}
        
        
