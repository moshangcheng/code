//20-09-07 21:11
//线形表堆栈Stack
template<class T>
class Stack {
public:
	Stack(int MaxStackSize = 10);
	~Stack() {
		delete[] stack;
	}
	bool IsEmpty() const {
		return top == -1;
	}
	bool IsFull() const {
		return top == MaxTop;
	}
	T Top() const;
	Stack<T>& Add(const T& x);
	Stack<T>& Delete(T& x);
private:
	int top;
	int MaxTop;
	T* stack;
};

template<class T>
Stack<T>::Stack(int MaxStackSize) {
	MaxTop = MaxStackSize;
	stack = new T[MaxTop];
	top = -1;
}

template<class T>
T Stack<T>::Top() const {
	return stack[top];
}

template<class T>
Stack<T>& Stack<T>::Add(const T& x) {
	stack[++top] = x;
	return *this;
}

template<class T>
Stack<T>& Stack<T>::Delete(T& x) {
	x = stack[top--];
	return *this;
}

