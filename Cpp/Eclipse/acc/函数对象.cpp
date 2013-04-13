#include <iostream>
#include <algorithm>
#include <cstdlib>
#include<time.h>

using namespace std;

class State {
	//a class which has id as its member
public:
	State() :
		m_id(0) {
	}
	void set_id(int id) {
		m_id = id;
	}
	int id() const {
		return m_id;
	}
private:
	int m_id;
};

struct PopLess: public std::binary_function<State, State, bool> {
	bool operator()(const State &a, const State &b) const {
		return a.id() < b.id();
	}
};

struct IsTen: public std::unary_function<State, bool> {
	bool operator()(const State &a) const {
		return a.id() == 10;
	}
};

int main(int argc, char *argv[]) {
	State st[10];

	srand((int) time(0));
	cout << "create st.............." << endl;
	for (int ix = 0; ix < 10; ix++) {
		int id = 1 + (int) (10.0 * rand() / (RAND_MAX + 1.0));
		st[ix].set_id(id);
		cout << st[ix].id() << endl;
	}
	cout << "create over............." << endl;

	sort(st, st + 10, PopLess());

	cout << "after sort st.............." << endl;
	for (int ix = 0; ix < 10; ix++) {
		cout << st[ix].id() << endl;
	}
	cout << "display over............." << endl;

	State *tenState = find_if(st, st + 10, IsTen());
	if (tenState != st + 10) {
		cout << "find 10" << endl;
	} else {
		cout << "can't find 10" << endl;
	}

	system("PAUSE");
	return 0;
}
