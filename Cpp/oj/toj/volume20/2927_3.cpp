#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
using namespace std;

int prt[100];
const int MAX = 1000000000;
struct CROSS { int h, i; };
struct NEIBR { int i, d; };

bool operator < (CROSS a, CROSS b)
{ return a.h < b.h; }

int root(int p) {
	if (prt[p] == p) return p;
	return prt[p] = root(prt[p]);
}

void joint(int a, int b) {
	int s1 = root(a);
	int s2 = root(b);
	if (s1 != s2) prt[s1] = s2;
}

int main()
{
    ifstream in("in.txt");
    CROSS height[100];
    vector<NEIBR> p[100];
    int t, n, m, besth, od, minh, maxh;
    int num[2], d[100], vst[100], t_vst[100];
    
    in >> t;
    while(t-- > 0) {
        in >> n >> m;
        for(int i = 0; i < n ; i++) {
            in >> height[i].h;
            height[i].i = i;
            p[i].clear();
        }
        for(int j = 0 ; j < m ; j++) {
            NEIBR x;
            int r, s, dist;
            in >> r >> s >> dist;
            r--; s--;
            x.i = r; x.d =dist;
            p[s].push_back( x ) ;
            x.i = s;   p[r].push_back( x );
        }
        if(n == 1) {
            cout<<0<<" "<<0<<endl;
            continue;
        }
        sort( height, height + n); 
        for(int i = 0 , j = 0 ; i < n ; i++) 
        if( height[i].i ==0 || height[i].i == (n-1)) 
        num[j++] = i;
                    
        besth = MAX;
        for(int i = num[0] ;i >= 0 ; i-- )  {
            if(i != 0 && height[i].h == height[i-1].h ) continue;
            minh = height[i].h;
            maxh = height[num[1]].h;
            memset(vst, 0, sizeof(vst));
            for(int j = 0 ; j < n ; j++) prt[j] = j;
            for(int j = i ; j < n ; j++ ) {
                od = height[j].i;
                vst[od] = 1;
                if(maxh < height[j].h ) maxh = height[j].h;
                if( maxh - height[i].h > besth ) break;
                for(int k = 0 ; k < p[od].size() ; k++)
                if( vst[ p[od][k].i ] == 1) joint( od, p[od][k].i);
                if(j < n-1 && height[j].h == height[j+1].h ) continue;
                if(root(0) == root(n-1) )  {
                    memcpy(t_vst, vst, sizeof(vst));
                    besth = maxh - minh;
                    break;
                }
            }
        }                 
        int mind, minp;
        memset( d, 0x3f, sizeof(d));
        d[0] = 0;
        while(1) {
            mind = MAX;  minp = -1;
            for(int k = 0 ; k < n ; k++ ) 
            if(t_vst[k] > 0 && d[k] < mind) {
                mind = d[k];
                minp = k;
            }
            if(minp == n-1 || minp == -1) break;
            t_vst[ minp ] = -t_vst[ minp ];
            for(int k = 0; k < p[minp].size() ; k++ ) 
            d[ p[minp][k].i ] <?= mind + p[minp][k].d;
        }                    
        cout<<besth<<" "<<d[n-1]<<endl;
    }
    system("pause");
    return 0;
}
            
            
                
            
            
