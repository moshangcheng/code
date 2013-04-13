#include <string>
#include <iomanip>
#include <iostream>
using namespace std;

int main()
{
    string s[100];
    double S[100], T[100], best;
    int i, j, ntest, width, height;
    cin >> ntest;
    while(ntest-- > 0)  {
        cin >> height >> width;
        for(i = 0; i < height; i++) cin >> s[i];
        for(i = 0; i < width; i++) {
            char c = s[height - 1][i];
            if(c == '.' || c == '*')    S[i] = 0;
            else S[i]= c - '0';
        }
        for(i = height - 2; i >= 0; i--) {
            for(j = 0; j < width; j++) {
                if(s[i][j] == '*') {
                    if(j == width-1) T[j] = (width > 1) ? S[j-1]:0;
                    else if(j == 0 )  T[j] = (width > 1) ? S[j+1]: 0;
                    else T[j] = (S[j-1] + S[j+1])/2;
                }
                else if(s[i][j] == '.') T[j] = S[j];
                else T[j] = s[i][j] - '0';
            }
            memcpy(S, T, sizeof(T));
        }
        best = 0;
        for(i = 0; i < width; i++) if(best < S[i]) best = S[i];
        cout.setf(ios::fixed);
        cout << setprecision(6) << best << endl;
    }
    return 0;
}
                    
                    
        
