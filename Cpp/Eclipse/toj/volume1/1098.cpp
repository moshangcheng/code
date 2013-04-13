#include <iostream>
#include <string>
using namespace std;


const int MAX = 201;
        
int main()
{
    int M, N;
    string str;
    cin >> N >> M;
    int s[MAX][2], f_b[MAX], f_s[MAX];
    while(N != 0 || M != 0) {
        memset(s, 0, sizeof(s));
        for(int i = 0; i < N; i++) {
            cin >> str;
            f_s[i] = str.find('S',0);
            f_b[i] = str.find('W',0);
        }
        for(int i = 0; i < N; i++) {
            if(i == 0) {
                s[0][0] = 0;
                if(f_b[i+1] > f_b[i]) s[0][1] = 0;
                else s[0][1] = -1;
                continue;
            }
            s[i][0] = (s[i-1][0] > s[i-1][1])? s[i-1][0] : s[i-1][1];
            
            //if((i < N-1 && f_b[i+1] < f_b[i]) || ( f_b[i-1] < f_b[i]))
    
            
            
            
            
        
        
        
