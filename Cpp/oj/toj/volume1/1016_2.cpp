#include <string>
#include <iostream>
using namespace std;

const int num_chars = 10;

struct Trie_node {
	int vlu;
    vector<pair<string, int> > data;
    Trie_node* branch[num_chars];
    Trie_node() {   
		vlu = 0;
		data.clear();
		memset(branch, 0, sizeof(branch)); 
	}
};

class Trie {
    public:
        Trie(): root(NULL){}
        Trie_node* Root() { return root; }
        int insert(const string& key, const string& data);
        Trie_node* search(const string& key) const;
    private:   
        Trie_node* root;
};

string convert(const string& a) {
	string b;
	for(int i = 0; i < a.size(); i++) b += c[a[i]-'a'];
	return b;
}

int main()
{
	string s, numb;
	int ntest, otest = 0;
	int i, j, k, tmp, m, nword;
	cin >> ntest;
	while(otest++ < ntest) {
		Trie Tree;
		cin >> nword;
		for(i = 0; i < nword; i++) {
			cin >> s >> tmp;
			Tree.insert(convert(s), s, tmp);
		}	
		cout << "Scenario #" << otest << ":\n";	
		cin >> m;
		for(i = 0; i < m; i++) {
			cin >> numb;
			if(numb[0] == '1') {
				cout << endl;
				continue;
			}
			cout << endl;
		}
		cout << endl;
	}
	return 0;
}

void Trie::insert(const string& key, const string& s, int vlu)
{
    if ( root == NULL ) root = new Trie_node;
    char char_code;
    Trie_node *location = root;
    string::const_iterator cnt = key.begin();

    while(cnt != key.end()) {
		location->vlu += vlu;
        char_code = *cnt - '0';
        if(location->branch[char_code] == NULL )
			location->branch[char_code] = new Trie_node;
        location = location->branch[char_code];
        cnt++;
    }
    data.push_back(make_pair(s, vlu));
}
