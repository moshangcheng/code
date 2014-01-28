#include <stdio.h>
#include <stdarg.h>

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
	int a0, a1, a2, a3, a4, a5, a6, a7, a8;
	va_start(args, a);
	a0 = va_arg(args, enum V);
	//printf( "get a0\n");
	a1 = va_arg(args, enum V);
	a2 = va_arg(args, enum  V);
	a3 = va_arg(args, enum  V);
	a4 = va_arg(args, enum V);
	a5 = va_arg(args, enum V);
	a6 = va_arg(args, enum V);
	a7 = va_arg(args, enum V);
	a8 = va_arg(args, enum V);
	va_end(args);
}

int main()
{
	/*int a[10];
	for(int i = 0; i < 10; i++) {
		a[i] = i;
	}
	
	V lv1 = V(0);*/
	vaf(-1, v1, v2, v3, v4, v5, v6, v7, v8, v9);
	return 0;
}
