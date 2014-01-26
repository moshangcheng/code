#include <iostream>

int main()
{
    int i;
    int * p = (int*) ((char*)&i + 1);

    printf("%d\n", *p);
}
