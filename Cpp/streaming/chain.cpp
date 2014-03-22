#include <iostream>
using namespace std;


template<typename I, typename O>
class Node {};

template<typename I, typename M, typename O>
void connect(Node<I, M> n1, Node<M, O> n2)
{
	return;
}


int main() {
	Node<bool, char> n1;
	Node<char, short> n2;
	Node<short, int> n3;

	connect(n1, n2);
	connect(n2, n3);
	return 0;
}