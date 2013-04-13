#include <iostream>
#include <string>
using namespace std;

const int MAXSIZE = 100;
const int BASE = 10000;

class BigInt
{
    public:
        BigInt(int l = 1) { len = l; memset(s, 0, sizeof(s)); }
        BigInt(const BigInt& b);
        void multiplyBASE();
        string tostring()const;
        int Len() const { return len; }
        int compare(const BigInt &b) const;
        BigInt& operator = (const BigInt &b);
        BigInt& operator = (const string& str);
        int& operator [] (int index) { return s[index]; }
        BigInt  operator + (const BigInt &b) const; //高精度加法
        BigInt  operator - (const BigInt &b) const; //高精度减法
        BigInt  operator * (int b) const;//高精度*单精度
        BigInt  operator * (const BigInt &b) const;
        BigInt  divide (int b, int &d) const;
        BigInt  divide (const BigInt &b, BigInt &d) const; 
    private:
        int len;
        int s[MAXSIZE];
};

int main()
{
    int x, y;
    BigInt a, b, c, d;
    string s1, s2;
    while(1) {
        cout << "Please input two big integers:\n";
        cin >> s1 >> s2;
        a = s1;    b = s2;
        
        c = a * b;
        cout << s1 << " * " << s2 << " = " << c.tostring() << endl;
        
        c = a.divide(b, d);
        cout << s1 << " / " << s2 << " = " ;
        cout << c.tostring() << "..." << d.tostring() << endl;
        
        c = a + b;
        cout << s1 << " + " << s2 << " = " << c.tostring() << endl;
        
        if(a.compare(b) >= 0) {
            cout << s1 << " - " << s2;
            c = a - b;
        }
        else {
            cout << s2 << " - " << s1;
            c = b - a;
        }
        cout << " = " << c.tostring() << endl;
        
        cout << "Please input a integer: \n";
        cin >> x;
        c = a * x;
        cout << s1 << " * " << x << " = " << c.tostring() << endl;
        c = b * x;
        cout << s2 << " * " << x << " = " << c.tostring() << endl;
        c = a.divide(x, y);
        cout << s1 << " / " << x << " = ";
        cout << c.tostring() << "..." << y << endl;
        c = b.divide(x, y);
        cout << s2 << " / " << x << " = ";
        cout << c.tostring() << "..." << y << endl;
        
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

//高精度减法, 保证 a >= b 
BigInt BigInt::operator - (const BigInt &b) const
{
    int i, length = len > b.len ? len: b.len;
    BigInt c(length);
    for(i = 0; i < length; i++)
    {
        c.s[i] += s[i] - b.s[i];
        if(c.s[i] < 0)
        {
            c.s[i] += BASE;
            c.s[i+1] --;
        }
    }
    while(c.len > 1 && c.s[c.len - 1]==0) c.len--;
    return c;
}

int BigInt::compare(const BigInt &b) const
{
    int length = len > b.len ? len: b.len;
    while(length > 0 && s[length-1] == b.s[length-1]) length--;
    if(length == 0) return 0;
    else return s[length - 1] - b.s[length - 1];
}

//高精度*单精度
BigInt BigInt::operator * (int b) const
{
    BigInt c(len);
    long long tp;
    for(int i = 0; i < c.len; i++)  {
        tp = c.s[i];
        tp += (long long)s[i] * b;
        c.s[i+1] += tp/BASE;
        c.s[i] = tp % BASE;
    }
    c.len++;
    while(c.s[c.len-1] >= BASE)   {
        c.s[c.len] += c.s[c.len-1]/BASE;
        c.s[c.len-1] %= BASE;
        c.len++;
    }
    while(c.len > 1 && c.s[c.len - 1] == 0) c.len--;
    return c;
}

//高精度*高精度
BigInt BigInt::operator * (const BigInt &b) const
{
    BigInt c;
    int i, j;
    for(i = 0; i < len; i++)
        for(j = 0; j < b.len; j++)  {
            c.s[i+j] += s[i] * b.s[j];
            c.s[i+j+1] += c.s[i+j]/BASE;
            c.s[i+j] %= BASE;
        }
    c.len = len + b.len;
    while(c.len > 1 && c.s[c.len - 1] == 0) c.len--;
    return c;
}

//高精度/单精度
//存在隐患， 对于单精度数b,设 BASE = 100, b = 20 00 00 00 00
//高精度数为10 00 00 00 00 00 00 ... d会增加到 10 00 00 00 00 00
//超过了整型数的范围, 所以建议 d 采用 long long int 
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

//高精度*BASE
void BigInt::multiplyBASE()     
{
    for(int i = len - 1; i >= 0; i--)   s[i+1] = s[i];
    s[0] = 0;
    len++;
    while(len > 1 && s[len - 1] == 0) len--;
}

//高精度/高精度 　{d为余数}
BigInt BigInt::divide (const BigInt &b, BigInt &d) const
{
    BigInt c(len);
    d.len = 1;
    memset(d.s, 0, sizeof(d.s));
    for(int i = len - 1; i >= 0; i--)
    {
        d.multiplyBASE();
        d.s[0] = s[i];
        while(d.compare(b) >= 0)  {
            d = d - b;
            c.s[i]++;
        }
    }
    while(c.len > 1 && c.s[c.len - 1] == 0) c.len--;
    return c;
}
