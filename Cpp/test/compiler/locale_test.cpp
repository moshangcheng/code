#include <iostream>
#include <locale.h>
using namespace std;

int main() {
    const char* lpCurrentLocaleName = ::setlocale(LC_ALL, NULL);
    printf("cuurent locale is: %s\n", lpCurrentLocaleName);
    const char* lpNewLocaleName = ::setlocale(LC_ALL, "iso_8859_1");
    printf("new locale is: %s\n", ::setlocale(LC_ALL, NULL));
    return 0;
}

