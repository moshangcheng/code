#include <iostream>
using namespace std;

struct V 
{
	int v;
};

void f(V& v)
{
	V v1 = {4};
	v = v1;
}

int main()
{
	V v = {3};
	f(v);
	cout << v.v << endl;
	return 0;
}
