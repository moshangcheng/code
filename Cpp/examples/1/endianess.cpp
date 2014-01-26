#include <iostream>

int main() {

	int num = 1;
	if(*(char *)&num == 1)
	{
		printf("\nLittle-Endian\n");
	}
	else
	{
		printf("Big-Endian\n");
	}
	return 0;
}
