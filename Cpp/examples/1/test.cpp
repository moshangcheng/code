#include <stdio.h>
#include <stdlib.h>
#include <uuid/uuid.h>

int main()
{
	uuid_t lUUID;
	uuid_generate(lUUID);
	printf("sizeof long is %d\n", sizeof(long));
	printf("sizeof unsigned long  is %d\n", sizeof(unsigned long));
	printf("sizeof unsigned long long  is %d\n", sizeof(unsigned long long));
	printf("hello world\n");
	return 0;
}
