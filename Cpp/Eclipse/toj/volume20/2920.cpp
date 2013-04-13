#include <cstdio>
using namespace std;

int main()
{
    long long n;
    while(scanf("%lld", &n) == 1) 
    printf("%lld\n", n * (n+1) * (n+2) / 6 );
    return 0;
}
