#include <stdio.h>

int main()
{
    int ntest, num, p;
    scanf("%d", &ntest);
    while(ntest-- > 0) {
        scanf("%d", &num);
        for(p = 0; !(num&1); p++) num >>= 1;
        printf("%d %d\n", num, p);
    }
    return 0;
}
                
