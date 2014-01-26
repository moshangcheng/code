#include <iostream>
#include <string>
#include <vector>
using namespace std;

string move[362880];
vector<pair<string, int> > L;
char drc[4] = {'d', 'l', 'u', 'r'};
int des[4][2] = {-1, 0, 0, 1, 1, 0, 0, -1};
int fct[10] = {1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880};

int convert(const string& s)
{
    int i, j, sum, m;
    for(sum = i = 0; i < 9; i++) {
        m = 0;
        for(j = i+1; j < 9; j++) 
            if(s[i] > s[j]) m++;
        sum += fct[s[i]-'1']*m;
    }
    return sum;
}

int main()
{
    string ss, s;
    pair<string, int> tp;
    int i, j, vlu, row, col, tr, tc;
    move[0] = "@";
    L.push_back(make_pair("123456789", 8));
    for(i = 0; i < L.size(); i++) {
        row = L[i].second/3;     col = L[i].second%3;
        for(j = 0; j < 4; j++) {
            tr = row + des[j][0];   tc = col + des[j][1];
            if(tr < 3 && tr >= 0 && tc < 3 && tc >= 0) {
                tp.first = L[i].first;
                tp.second = tr*3 + tc;
                tp.first[L[i].second] = tp.first[tp.second];
                tp.first[tp.second] = '9';
                vlu = convert(tp.first);
                if(move[vlu].size() == 0) {
                    L.push_back(tp);
                    move[vlu] = move[convert(L[i].first)] + drc[j];
                }
            }
        }
    }
    while(getline(cin, ss)) {
        s.clear();
        for(i = 0; i < ss.size(); i++)
            if(ss[i] == 'x') s += '9';
            else if(ss[i] != ' ') s += ss[i];
        vlu = convert(s);
        s = move[vlu];
        if(s.size() == 0) cout << "unsolvable\n";
        else {
            for(i = s.size()-1; i > 0; i--) cout << s[i];
            cout << endl;
        }
    }
    return 0;
}
