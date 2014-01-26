#include <iostream>
#include <string>
using namespace std;

const int MAXN = 15;
const int BOUND = MAXN*9;
long long len, nb, s[MAXN + 1][BOUND + 1];
string A, B, C, mine[MAXN + 1][BOUND + 1];

void cpt(int flag, int sum, int depth)
{
    if(sum < 0) return;
    if(depth == len) {
        if(sum == 0) nb++;
        return;
    }
    if(flag > 0) {
        for(int i = 0; (i + '0') < B[depth] && i <= sum; i++)
        if(s[len- depth - 1][sum - i] > 0) {
            if(nb == 0) 
            C += (char)(i + '0') + mine[len - depth - 1][sum - i];
            nb += s[len- depth - 1][sum - i];
        }
        if(nb == 0) C += B[depth];
        cpt(flag, sum - B[depth] + '0', depth + 1);
        if(nb == 0) C.erase(C.size() - 1);
    }
    else if(flag < 0) {
        if(nb == 0) C += A[depth];
        cpt(flag, sum - A[depth] + '0', depth + 1);
        if(nb == 0) C.erase(C.size() - 1);
        for(int i = A[depth] - '0' + 1; i < 10 && i <= sum; i++)
        if(s[len - depth - 1][sum - i] > 0) {
            if(nb == 0) 
            C += (char)(i + '0') + mine[len - depth - 1][sum - i];
            nb += s[len - depth - 1][sum - i];
        }
    }
}      
    
int main()
{
    int i, j, k, S;
    memset(s, 0, sizeof(s));
    s[0][0] = 1;
    for(i = 1; i <= MAXN; i++)
    for(j = 0; j < 10; j++)
    for(k = 0; k <= (i-1)*9; k++)
    if(s[i-1][k] > 0) {
        if(s[i][k+j] == 0) 
        mine[i][k+j] = (char)(j+'0') + mine[i-1][k];
        s[i][k+j] += s[i-1][k];
    }
    while(cin >> A >> B >> S) {
        C.clear();  nb = 0;
        len = (A.size() > B.size()) ? A.size(): B.size();
        A.insert(0, len - A.size(), '0');
        B.insert(0, len - B.size(), '0');
        for(i = 0; i < len && A[i] == B[i]; i++) S -= A[i] - '0';
        if(i == len) {
            cout << (S == 0) << endl << B << endl;
            continue;
        }
        len -= i;
        C.append(A, 0, i);
        A.erase(0, i);
        B.erase(0, i);
        if(nb == 0) C += A[0];
        cpt(-1, S - A[0] + '0', 1);
        if(nb == 0) C.erase(C.size()-1);
        for(i = A[0] + 1; i < B[0]; i++)
        if(S >= i-'0') {
            if(nb == 0 && s[len-1][S - i +'0'] > 0)
            C = (char)i + mine[len-1][S - i + '0'];
            nb += s[len-1][S - i +'0'];
        }
        if(nb == 0) C += B[0];
        cpt( 1, S - B[0] + '0', 1);
        if(nb == 0) C.erase(C.size() - 1);
        cout << nb << endl;
        for(i = 0; i < C.size() && C[i] == '0'; i++);
        for(; i < C.size(); i++) cout << C[i];
        cout << endl;
    }
    return 0;
}
        
    
