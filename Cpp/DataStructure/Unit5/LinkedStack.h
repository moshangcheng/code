template<class T> class LinkedStack;

template<class T>
class Node {
private:
	friend class LinkedStack<T> ;
	T data;
	Node<T>* link;
};

template<class T>
class LinkedStack {
public:
	LinkedStack() {
		top = 0;
	}
	~LinkedStack();
	bool IsEmpty() const {
		return top == 0;
	}
	T Top() const;
	LinkedStack<T>& Add(const T& x);
	LinkedStack<T>& Delete(T& x);
private:
	Node<T> *top;
};

template<class T>
LinkedStack<T>::~LinkedStack() {
	Node<T>* next;
	while (top) {
		next = top->link;
		delete top;
		top = next;
	}
}

template<class T>
T LinkedStack<T>::Top() const {
	return top->data;
}

template<class T>
LinkedStack<T>& LinkedStack<T>::Add(const T& x) {
	Node<T>* p = new Node<T> ;
	p->data = x;
	p->link = top;
	top = p;
	return *this;
}

template<class T>
LinkedStack<T>& LinkedStack<T>::Delete(T& x) {
	x = top->data;
	Node<T>*p = top;
	top = top->link;
	delete p;
	return *this;
}

