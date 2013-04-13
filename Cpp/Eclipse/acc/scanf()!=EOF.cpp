#include <iostream>
using namespace std;

int main()
{
    /*unsigned a, b;
    while(scanf("%u%u", &a, &b) == 2) { 
        printf("%u %u\n", a, b);
    }*/
    //无符号数很特殊，使用scanf无法判别，须使用 cin
    unsigned a, b;
    while(cin >> a >> b)  {
        cout << a << b << endl;
    } 
    
    /*char s[100];
    while(gets(s) != NULL) {
        printf("%s \n", s);
    }*/
    //建议使用  gets()， 使用 scanf() 遇到文件尾时须两次才可以结束 
    return 0;
}
