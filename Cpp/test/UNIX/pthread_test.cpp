#include <iostream>
#include <cstdio>
#include <pthread.h>

void* print(void* v) {
    int* p = reinterpret_cast<int*>(v);
    printf("%d\n", *p);
    if(*p > 5) {
        int* p2 = (int*)0x1;
        *p2 = 3;
    }
}

int main() {
    pthread_t p[10];
    int i;
    for(i = 0; i < 10; i++) {
        pthread_create(&p[i], NULL, &print, &i);
    }
    return 0;
}
