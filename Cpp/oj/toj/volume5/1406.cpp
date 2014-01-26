#include <iostream>
using namespace std;

int D, W;
char hi[1024][2048];
int power[11] = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024};

void init(int depth)
{
	if(depth == 0)  return;
    init(depth-1);
    int d = power[depth], w = 2*d, d0 = D-d;        
    for(int i = 0; i < d; i++)
    for(int j = 0; j < w; j++) 
    	hi[d0+i-d][w/2+j] = hi[d0+i][w+j]= hi[d0+i][j];
}        
    
int main()
{
	int i, j, n;
    while(cin >> n && n > 0) {
        D = power[n];
        W = 2*D;
        memset(hi, ' ', sizeof(hi));
        hi[D-2][1] = hi[D-1][0] = '/';
        hi[D-2][2] = hi[D-1][3] = '\\';
        hi[D-1][1] = hi[D-1][2] = '_';
        init(n-1);
        for(i = 0; i < D;i++) {
            for(j = 0; j <= W/2.0+i; j++) 
				cout << hi[i][j];
            cout << endl;
        }
        cout << endl;
    }
    return 0;
}
        
