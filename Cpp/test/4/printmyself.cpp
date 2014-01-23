#include <cstdio>
#include <cstdlib>
using namespace std;
int main()
{
    char*a="main(){char*a=%c%s%c;printf(a,34,a,34);}";
    printf(a,34,a,34);
    system("pause");
}
