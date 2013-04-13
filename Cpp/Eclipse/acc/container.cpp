#include <iostream>
#include <list>
using namespace std;

int main() {
	list<int> L;
	list<int>::value_type x;
	list<int>::reference a = x;
	list<int>::pointer p = &x;
	list<int>::size_type n;
	list<int>::iterator cnt;

	cin >> n;
	for (int i = 0; i < n; i++)
		L.push_back(i % 4);
	cout << n << " " << L.size() << endl;

	cin >> x;
	cout << *p << " " << x << " " << a << endl;
	L.push_back(a);

	for (cnt = L.begin(); cnt != L.end(); cnt++)
		cout << *cnt << " ";
	cout << endl;
	system("pause");
	return 0;
}
