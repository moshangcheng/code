#include <cstdio>
using namespace std;

int vlu[300000];
int map[300000];

void swap(int& a, int& b)
{ int c = a;  a = b;  b = c; }

int main()
{
    int i, j, t1, t2, d, size, anti;
    while(scanf("%d", &size) == 1) {
        if(size == 0) break;
        for(i = 0; i < size*size; i++) {
            scanf("%d", &j);
            j--;
            if(j < 0) {
                j += size*size;
                t1 = i;
            }
            vlu[i] = j;
        }
        for(i = 0; i < size*size; i++) {
            scanf("%d", &j);
            j--;
            if(j < 0) {
                j += size*size;
                t2 = i;
            }
            map[j] = i;
        }
        for(i = 0; i < size*size; i++) vlu[i] = map[vlu[i]];
        anti = 0;
        for(i = 0; i < size*size; i++)
            while(vlu[i] != i) {
                anti++;
                swap(vlu[i], vlu[vlu[i]]);
            }
        d = (t1%size - t2%size);
        if(d < 0)  d = -d;
        d += (t1/size-t2/size)*((t1 > t2) ? 1: -1);
        if((anti&1) == (d&1))   printf("Yes\n");
        else printf("No\n");
    }
    return 0;
}
