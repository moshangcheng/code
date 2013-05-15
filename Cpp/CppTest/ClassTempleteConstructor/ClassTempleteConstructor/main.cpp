#include <iostream>
#include <cstdarg>
using namespace std;

enum V {
        v1,
        v2,
        v3,
        v4,
        v5,
        v6,
        v7,
        v8,
        v9
};

void vaf(int a, ...)
{
        va_list args;
        va_start(args, a);
        V* a0 = va_arg(args, V*);
        int a1 = va_arg(args, V);
        int a2 = va_arg(args, V);
        int a3 = va_arg(args, V);
        int a4 = va_arg(args, V);
        int a5 = va_arg(args, V);
        int a6 = va_arg(args, V);
        int a7 = va_arg(args, V);
        int a8 = va_arg(args, V);
        va_end(args);
}

int main()
{
        int a[10];
        for(int i = 0; i < 10; i++) {
                a[i] = i;
        }

		V lv1 = V(1);
        vaf(-1, &lv1, v2, v3, v4, v5, v6, v7, v8, v9);
        return 0;
}
