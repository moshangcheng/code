class LinearList {
public:
	LinearList(int MaxListSize = 10);//构造函数
	~LinearList() {
		delete[] element;
	}//析构函数
	bool IsEmpty() {
		return length == 0;
	}
	int Length() const {
		return length;
	}
	bool Find(int k, T& x) const;
	int Search(const T& x) const;
	LinearList<T>& Delete(int k, T& x);
	LinearList<T>& Insert(int k, const T& x);
	void Output(ostream& out) const;
private:
	int length;
	int MaxSize;
	T* element;
};

template<class T>
LinearList<T>::LinearList(int MaxListSize) {
	MaxSize = MaxListSize;
	element = new T[MaxSize];
	length = 0;
}

template<class T>
bool LinearList<T>::Find(int k, T& x) const {
	if (k < 1 || k > length)
		return false;
	x = element[k - 1];
	return true;
}

template<class T>
int LinearList<T>::Search(const T& x) const {
	for (int i = 0; i < length; i++)
		if (element[i] == x)
			return ++i;
	return 0;
}

template<class T>
LinearList<T>& LinearList<T>::Delete(int k, T& x) {
	for (int i = k; i < length; i++)
		element[i - 1] = element[i];
	length--;
	return *this;
}

template<class T>
LinearList<T>& LinearList<T>::Insert(int k, const T& x) {
	for (int i = length - 1; i >= k; i--)
		element[i + 1] = element[i];
	element[k] = x;
	length++;
	return *this;
}

template<class T>
void LinearList<T>::Output(ostream& out) const {
	for (int i = 0; i < length; i++)
		out << element[i] << " ";
}

template<class T>
ostream& operator<<(ostream& out, const LinearList<T>& x) {
	x.Output(out);
	return out;
}
