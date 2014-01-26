#include <iostream>
#include <langinfo.h>
using namespace std;

int main() {
    setlocale(LC_ALL, "fr_FR"); 
    printf("%s\n", nl_langinfo(D_FMT));
    return 0;
}

