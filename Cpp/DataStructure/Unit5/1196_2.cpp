#include <iostream>
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
	string cmd, site;
	while (cin >> cmd) {
		if (cmd == "QUIT")
			break;
		else if (cmd == "BACK")
			BACK();
		else if (cmd == "FORWARD")
			FORWARD();
		else if (cmd == "VISIT") {
			cin >> site;
			VISIT(site);
		}
	}
	return 0;
}

