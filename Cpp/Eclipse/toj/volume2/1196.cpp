#include <iostream>
#include <fstream>
#include <string>
using namespace std;

string back_stack[100];
string for_stack[100];
string current = "http://www.acm.org/";
int cnt_b = -1, cnt_f = -1;

void BACK() {
	if (cnt_b < 0)
		cout << "Ignored\n";
	else {
		for_stack[++cnt_f] = current;
		cout << (current = back_stack[cnt_b--]) << endl;
	}
}

void FORWARD() {
	if (cnt_f < 0)
		cout << "Ignored\n";
	else {
		back_stack[++cnt_b] = current;
		cout << (current = for_stack[cnt_f--]) << endl;
	}
}

void VISIT(string site) {
	cnt_f = -1;
	back_stack[++cnt_b] = current;
	cout << (current = site) << endl;
}

int main() {
	ifstream in("C:\\Documents and Settings\\moshangcheng\\桌面\\in.txt");
	string cmd, site;
	while (in >> cmd) {
		if (cmd == "QUIT")
			break;
		else if (cmd == "BACK")
			BACK();
		else if (cmd == "FORWARD")
			FORWARD();
		else if (cmd == "VISIT") {
			in >> site;
			VISIT(site);
		}
	}
	system("pause");
	return 0;
}

