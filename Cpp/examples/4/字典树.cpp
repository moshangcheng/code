#include <string>
#include <iostream>
using namespace std;

const int num_chars = 26;

struct Trie_node {
	string data;
	Trie_node* branch[num_chars];
	Trie_node() {
		memset(branch, 0, sizeof(branch));
	}
};

class Trie {
public:
	Trie() :
		root(NULL) {
	}
	void printall(Trie_node *p);
	Trie_node* Root() {
		return root;
	}
	int insert(const string& key, const string& data);
	Trie_node* search(const string& key) const;
private:
	Trie_node* root;
};

Trie_node* Trie::search(const string& key) const {
	char char_code;
	Trie_node *location = root;
	string::const_iterator cnt = key.begin();

	while (location != NULL && cnt != key.end()) {
		if (*cnt >= 'A' && *cnt <= 'Z')
			char_code = *cnt - 'A';
		else if (*cnt >= 'a' && *cnt <= 'z')
			char_code = *cnt - 'a';
		else
			return NULL;//非法字符
		location = location->branch[char_code];
		cnt++;
	}
	if (location != NULL && !location->data.empty())
		return location;
	else
		return NULL;//未找到
}

int Trie::insert(const string& key, const string& data) {
	if (root == NULL)
		root = new Trie_node;
	char char_code;
	Trie_node *location = root;
	string::const_iterator cnt = key.begin();

	while (cnt != key.end()) {
		if (*cnt >= 'A' && *cnt <= 'Z')
			char_code = *cnt - 'A';
		else if (*cnt >= 'a' && *cnt <= 'z')
			char_code = *cnt - 'a';
		else
			return -1;//非法字符
		if (location->branch[char_code] == NULL)
			location->branch[char_code] = new Trie_node;
		location = location->branch[char_code];
		cnt++;
	}
	if (!location->data.empty())
		return 0;
	location->data = data;
	return 1;
}

void Trie::printall(Trie_node *p) {
	if (!p->data.empty())
		cout << p->data << endl;
	for (int i = 0; i < num_chars; ++i)
		if (p->branch[i] != NULL)
			printall(p->branch[i]);
}

int main() {
	Trie t;
	int nstring;
	string data, key;
	cout << "Please input the number of strings:\n";
	cin >> nstring;
	for (int i = 0; i < nstring; i++) {
		cin >> key >> data;
		t.insert(key, data);
	}
	t.printall(t.Root());
	system("pause");
	return 0;
}
