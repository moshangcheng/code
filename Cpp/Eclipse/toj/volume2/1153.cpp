#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
using namespace std;

int main()
{
    int ntest;
    string s, word;
    cin >> ntest;
    getline(cin, s, '\n');
    while(ntest-- > 0) {
        getline(cin, s, '\n');
        istringstream is(s);
        is >> word;
        reverse(word.begin(), word.end());
        cout << word;
        while(is >> word){
            reverse(word.begin(), word.end());
            cout << " " << word;
        }
        cout << endl;
    }
    return 0;
}
        
