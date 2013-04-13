#include <iostream>
#include <string>
using namespace std;

const int MAXSIZE = 150;
const int BASE = 100000000;
const int MAXNUM = 5000;

class BigInt
{
    public:
        BigInt(int l = 1) { len = l; memset(s, 0, sizeof(s)); }
        BigInt(const BigInt& b);
        string tostring()const;
        BigInt& operator = (const BigInt &b);
        BigInt& operator = (const string& str);
        BigInt  operator + (const BigInt &b) const; //高精度加法
    private:
        int len;
        int s[MAXSIZE];
};

BigInt f[MAXNUM];

int main()
{
	f[0] = f[1] = "1";
	for(int i = 2; i < MAXNUM; i++)
		f[i] = f[i-1] + f[i-2];
	int n;
	while(cin >> n)
		cout << f[n-1].tostring() << endl;
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

string BigInt::tostring() const
{
    int i, j;
    string str;
    for(i = len - 1; i >= 0; i--)
    for(j = BASE; j > 1; j /= 10) str += s[i]%j/(j/10) + '0';
    for(i = 0; str[i] == '0' && i < str.size()-1; i++);
    str.erase(0, i);
    return str;
}

//高精度加法
BigInt BigInt::operator + (const BigInt &b) const
{
    int i, length = len > b.len ? len: b.len;
    BigInt c(length);
    for(i = 0; i < length; i++)
    {
        c.s[i] += s[i] + b.s[i];
        if(c.s[i] >= BASE)
        {
            c.s[i] -= BASE;
            c.s[i+1] ++;
        }
    }
    if(c.s[c.len] > 0) c.len++;
    while(c.len > 1 && c.s[c.len - 1] == 0) c.len--;
    return c;
}
