#include <iostream>
#include <string>
using namespace std;

const int MAXSIZE = 15;
const int BASE = 1000000000;

class BigInt
{
    public:
        BigInt(int l = 1) { len = l; memset(s, 0, sizeof(s)); }
        BigInt(const BigInt& b);
        BigInt& operator = (const BigInt &b);
        BigInt& operator = (const string& str);
        BigInt  divide (int b, int &d) const;
    private:
        int len;
        int s[MAXSIZE];
};

const int MAX = 1010000;
bool notp[MAX];//素数判定
int pr[80000];//pr存放素数,pn当前素数个数。

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
    string str;
    int bound, res;
    BigInt n;
    while(cin >> str >> bound) {
         if(str == "0" && bound == 0) break;
         n = str;
         for(i = 0; pr[i] < bound; i++) {
            n.divide(pr[i], res);
            if(res == 0) break;
         }
         if(pr[i] >= bound) cout << "GOOD\n";
         else cout << "BAD " << pr[i] << endl;
   }
   return 0;
}

BigInt::BigInt(const BigInt &b)  {
    len = b.len;
    memset(s, 0, sizeof(s));
    for(int i = 0; i < len; i++) s[i] = b.s[i];
}

BigInt& BigInt::operator = (const BigInt &b)  {
    len = b.len;
    memset(s, 0, sizeof(s));
    for(int i = 0; i < len; i++) s[i] = b.s[i];
    return *this;
}

BigInt& BigInt::operator = (const string& S)
{
    int i, j, sum, t;
    string str = S;
    for(i = 0; str[i] == '0' && i < str.size()-1; i++);
    str.erase(0, i);
    memset(s, 0, sizeof(s));
    for(j = sum = 0, t = 1, i = str.size()-1; i >= 0; i--) {
        sum += (str[i] - 48)*t;
        if(t*10 == BASE) {
            t = 1;
            s[j++] = sum;
            sum = 0;
        }
        else t *= 10;
    }
    if(t > 1) s[j++] = sum;
    len = j;
    return *this;
}


//高精度/单精度
BigInt BigInt::divide (const int b, int &d) const 
{
    int i;
    long long res;
    BigInt c(len);
    for(res = 0, i = len-1; i >= 0;i--)  {
        res = res *BASE + s[i];
        c.s[i] = res / b;
        res %= b;
    }
    d = (int)res;
    while(c.len > 1 && c.s[c.len - 1] == 0) c.len--;
    return c;
}
