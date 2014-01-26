#include <iostream>
using namespace std;

int main() {
	int Value[500001], n;
	bool Order[4000000];
	memset(Order, 0, 1);
	Value[0] = 0;
	Order[0] = 1;
	for (int i = 1; i < 500001; i++) {
		if (Value[i - 1] - i > 0 && Order[Value[i - 1] - i] == 0)
			Value[i] = Value[i - 1] - i;
		else
			Value[i] = Value[i - 1] + i;
		Order[Value[i]] = 1;
	}
	while (cin >> n && n != -1)
		cout << Value[n] << endl;
	return 0;
}
