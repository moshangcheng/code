#include <iostream>
using namespace std;

struct InnerStruct {
	bool v1;
	char v2;
	int v3;
	long v4;
	double v5;
};

struct OuterStruct {
	bool a;
	InnerStruct b;
	int c;
};


struct InnerStructBuffer {
	bool a;
	char b[sizeof(InnerStruct)];
	int c;
};

int main() {
	printf ("check size of basic types\n");
	printf ("size of bool is: %d\n", sizeof(bool));
	printf ("size of char is: %d\n", sizeof(char ));
	printf ("size of int is: %d\n", sizeof(int));
	printf ("size of long is: %d\n", sizeof(long));
	printf ("size of double is: %d\n", sizeof(double));

	InnerStruct is;
	printf ("\nsize of InnerStruct is: %d\n", sizeof(is));

	printf ("\nmemory alignment\n");
	OuterStruct os;
	printf ("%p\n", &os.a);
	printf ("%p\n", &os.b);
	printf ("%p\n", &os.c);
	InnerStruct* pIS1 = &os.b;
	printf ("access member of InnerStruct: %d\n", pIS1->v3);

	printf ("\nmake missalignment\n");
	InnerStructBuffer isb;
	printf ("%p\n", &isb.a);
	printf ("%p\n", isb.b);
	printf ("%p\n", &isb.c);
	InnerStruct* pIS2 = (InnerStruct*)isb.b;
	printf ("access member of InnerStruct: %d\n", pIS2->v3);
};
