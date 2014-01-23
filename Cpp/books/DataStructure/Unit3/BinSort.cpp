#include <iostream>
#include <cstdlib>
#include "Chain.h"
using namespace std;

class Node {
public:
	friend int main();
	friend int F1(Node& x);
	friend int F2(Node& x);
	friend int F3(Node& x);
	friend void
	BinSort(Chain<Node>& X, int range, int(*value)(Node& x));
	friend ostream& operator<<(ostream& out, const Node& x);
private:
	int score1;
	int score2;
	int score3;
	int name;
};

ostream& operator<<(ostream& out, const Node& x) {
	out << x.name << " ";
	return out;
}

inline int F1(Node& x) {
	return x.score1;
}
inline int F2(Node& x) {
	return x.score2;
}
inline int F3(Node& x) {
	return x.score3;
}

void BinSort(Chain<Node>& X, int range, int(*value)(Node& x)) {
	int len = X.Length();
	Node x;
	Chain<Node>*bin;
	bin = new Chain<Node> [range + 1];
	for (int i = 1; i <= len; i++) {
		X.Delete(1, x);
		bin[value(x)].Insert(0, x);
	}
	for (int j = range; j > -1; j--)
		while (!bin[j].IsEmpty()) {
			bin[j].Delete(1, x);
			X.Insert(0, x);
		}
	delete[] bin;
}

int main() {
	Node x;
	Chain<Node> L;
	for (int i = 10; i > 0; i--) {
		int maxrand = 20;
		x.score1 = rand() % maxrand;
		x.score2 = rand() % maxrand;
		x.score3 = rand() % maxrand;
		x.name = i;
		L.Insert(0, x);
	}
	BinSort(L, 100, F1);
	cout << "Sort on score1 " << endl << L << endl;
	BinSort(L, 100, F2);
	cout << "Sort on score2 " << endl << L << endl;
	BinSort(L, 100, F3);
	cout << "Sort on score3 " << endl << L << endl;
	system("pause");
	return 0;
}
