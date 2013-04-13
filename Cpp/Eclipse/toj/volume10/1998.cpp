#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

struct DNA { string s; int d; };

bool operator < (DNA a, DNA b)
{ return (a.d < b.d); }

int main()
{
    DNA t;
    vector<DNA> L;
    string tp,c = "ACGT";
    int i, j, k, nstring, length, d;
    while(cin >> length >> nstring)  {
        L.clear();
        for(i = 0; i < nstring ; i++) {
            cin >> tp;
            t.s = tp;   t.d = 0;
            for(j = 0; j < c.size(); j++) 
            for(k = 0; k < tp.size(); k++) 
            if(tp[k] == c[j]) {
                tp.erase(k, 1);
                t.d += k--;  
            }
            L.push_back(t);
        }
        stable_sort(L.begin(), L.end());
        for(i = 0; i < nstring; i++) cout << L[i].s << endl;
    }
    return 0;
}
