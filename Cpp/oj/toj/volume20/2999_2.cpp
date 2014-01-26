#include <set>
#include <list>
#include <string>
#include <sstream>
#include <iostream>
#include <algorithm>
using namespace std;

list<int> L;
set<string> S[1000];
pair<string,int> title[1000];

bool inline cmp (const pair<string,int>& a, const pair<string,int>& b)
{ return a.second > b.second; }

int main()
{
    string str, word;
    istringstream is;
    int i, j, vlu, n, m;
    list<int>::iterator cnt, prev;
    while(cin >> n && n > 0) {
        for(i = 0; i < n; i++) {
            getline(cin, title[i].first);
            getline(cin, title[i].first);
            cin >> title[i].second;
         }
         stable_sort(title, title + n, cmp);
         for(i = 0; i < n; i++) {
            is.clear();
            is.str(title[i].first);
            while(is >> word) {
                for(j = 0; j < word.size(); j++) {
                    if(word[j] <= 'Z' && word[j] >= 'A') 
                    word[j] += 'a'-'A';  
                } 
                S[i].insert(word);
            }
        }
        cin >> m;
        getline(cin, str);
        for(i = 0; i < m; i++) {
            L.clear();
            getline(cin, str);
            is.clear();
            is.str(str);
            for(j = 0; j < n; j++) L.push_back(j);
            while(is >> word) {
                for(j = 0; j < word.size(); j++) {
                    if(word[j] <= 'Z' && word[j] >= 'A') 
                    word[j] += 'a'-'A'; 
                }
                for(cnt = L.begin(); cnt != L.end();) {
                    prev = cnt++;
                    if(S[*prev].count(word) == 0) L.erase(prev);  
                }
            }
            for(cnt = L.begin(); cnt != L.end(); cnt++) 
                cout << title[*cnt].first << endl;
            cout << "***\n";
        }
        cout << "---\n";
    }
    return 0;
}
