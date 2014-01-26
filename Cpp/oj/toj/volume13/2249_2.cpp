#include <cstdio>
using namespace std;

int vlu[300000];
int map[300000];

void swap(int& a, int& b)
{ int c = a;  a = b;  b = c; }

int main()
{
    int i, j, t, size, anti;
    while(scanf("%d", &size) == 1) {
        if(size == 0) break;
        for(i = 0; i < size*size; i++) {
            scanf("%d", &j);
            j--;
            if(j < 0) j += size*size;
            vlu[i] = j;
        }
        for(i = 0; i < size*size; i++) {
            scanf("%d", &j);
            j--;
            if(j < 0) j += size*size;
            map[i] = j;
        }
        for(i = 0; i < size*size; i++) {
            vlu[i] = map[vlu[i]];
            if(vlu[i] == size*size-1) t = i;
        }
        anti = 0;
        for(i = 0; i < size*size; i++)
            while(vlu[i] != i) {
                anti++;
                swap(vlu[i], vlu[vlu[i]]);
            }
        if((anti&1) == ((size*2 - 2- t/size - t%size)&1)) 
            printf("Yes\n");
        else printf("No\n");
    }
    return 0;
}
