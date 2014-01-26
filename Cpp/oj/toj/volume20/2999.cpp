#include <iostream>
#include <string>
#include <sstream>
#include <list>
#include <map>
#include <algorithm>
using namespace std;

list<int> L;
pair<string,int> title[1000];
map<string,int> M[1000];

int main()
{
    string str, word;
    int i, j, vlu, n, m;
    list<int>::iterator cnt, prev, next;
    while(cin >> n && n > 0) {
        for(i = 0; i < n; i++) {
            getline(cin, title[i].first);
            getline(cin, title[i].first);
            cin >> title[i].second;
            istringstream is(title[i].first);
            while(is >> word) {
                for(j = 0; j < word.size(); j++) {
                    if(word[j] <= 'Z' && word[j] >= 'A') 
                    word[j] += 'a'-'A';  
                } 
                M[i][word] = title[i].second;
            }
        }
        cin >> m;
        getline(cin, str);
        for(i = 0; i < m; i++) {
            getline(cin, str);
            istringstream is(str);
            L.clear();
            for(j = 0; j < n; j++) L.push_back(j);
            while(is >> word) {
                for(j = 0; j < word.size(); j++) {
                    if(word[j] <= 'Z' && word[j] >= 'A') 
                    word[j] += 'a'-'A'; 
                }
                for(cnt = L.begin(); cnt != L.end();) {
                    prev = cnt++;
                    if(M[*prev].count(word) == 0) L.erase(prev);  
                }
            }
            for(cnt = L.begin(); cnt != L.end(); cnt++) {
                next = cnt;
                for(next++; next != L.end(); next++)
                    if(title[*next].second > title[*cnt].second) {
                        vlu = *cnt;
                        *cnt = *next;
                        *next = vlu;
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
            
            
            
