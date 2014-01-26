#include<iostream>
using namespace std;

int mas[5200];
int vlu[100000];

int main()
{
    int n, l, u, i, j, max, cnt, last, id;
    while (cin >> n >> l >> u) {
        for (i = 0; i < n; i++) cin >> vlu[i];
        max = -1;
        id = 0;
        for (i = l; i <= u; i++){
            cnt = 0;
            memset (mas, 0, sizeof(mas));
            mas[0] = 1;
            last = 0;
            for (j = 0; j < n; j++){
                last =(last + vlu[j]) % i;
                cnt += mas[last];
                mas[last]++;
            }
            if (max < cnt){
                max = cnt;
                id = i;
            }
        }
        cout << id << endl;
    }
    return 0;
}
