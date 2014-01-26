template<class T>
class IndirectList {
public:
	IndirectList(int MaxListSize = 10);
	~IndirectList();
	bool IsEmpty() const {
		return length == 0;
	}
	int Length() const {
		return length;
	}
	bool Find(int k, T& x) const;
	int Search(const T& x) const;
	IndirectList<T>& Delete(int k, T& x);
	IndirectList<T>& Insert(int k, const T& x);
	void Output(ostream& out) const;
private:
	T**table;
	int length, MaxSize;
};

template<class T>
IndirectList<T>::IndirectList(int MaxListSize) {
	MaxSize = MaxListSize;
	table = new T*[MaxSize];
	length = 0;
}

template<class T>
IndirectList<T>::~IndirectList() {
	for (int i = 0; i < length; i++)
		delete table[i];
	delete[] table;
}

template<class T>
bool IndirectList<T>::Find(int k, T& x) const {
	if (k < 1 || k > length)
		return false;
	x = *table[k - 1];
	return true;
}

template<class T>
int IndirectList<T>::Search(const T& x) const {
	int i;
	for (i = 0; i < length; i++)
		if (*table[i] == x)
			return ++i;
	return 0;
}

template<class T>
IndirectList<T>& IndirectList<T>::Delete(int k, T& x) {
	x = *table[k - 1];
	for (int i = k; i < length; i++)
		table[i - 1] = table[i];
	length--;
	return *this;
}

template<class T>
IndirectList<T>& IndirectList<T>::Insert(int k, const T& x) {
	for (int i = length - 1; i >= k; i--)
		table[i + 1] = table[i];
	table[k] = new T;
	*table[k] = x;
	length++;
	return *this;
}

template<class T>
void IndirectList<T>::Output(ostream& out) const {
	for (int i = 0; i < length; i++)
		out << *table[i] << " ";
}

template<class T>
ostream& operator<<(ostream& out, const IndirectList<T>& x) {
	x.Output(out);
	return out;
}

