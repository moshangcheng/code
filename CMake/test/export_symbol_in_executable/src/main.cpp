#include "main.h"
#include "../lib/hello.h"

void main_hello() {
	printf("hello from main\n");
}

int main() {
	lib_hello();
	return 0;
}

