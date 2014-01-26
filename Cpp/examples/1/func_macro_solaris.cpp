#include <stdio.h>
#include <string.h>

#define FUNC __func__

#define I__func__ strlen(FUNC)

void myfunc(void)
{
    printf("%d\n", strlen(__func__));
}

int main() {
    myfunc();
    return 0;
}
