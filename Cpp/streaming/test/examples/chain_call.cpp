#include <memory>
#include <iostream>

class Node {
public:

	Node(Node * p) : prev(p), id(p->id+1) {}

	Node() : id(0) , prev(NULL) {}

	static Node* head() {
		return new Node();
	}

	Node* next() {
		return new Node(this);
	}

	void work() {
		std::cout << "level " << id << " starts to work\n";
		if(prev != NULL)
		{
			prev->work();
		}
		std::cout << "level " << id << " fnished work\n";
	}

	~Node() {
		std::cout << "level " << id << " destoryed\n";
	}

private:
	int id;
	std::shared_ptr<Node> prev;
};

int main() {

	std::shared_ptr<Node> chain(Node::head()->next()->next()->next());

	chain->work();

	return 0;
}