//20-09-07 08:09
//模板一维数组类，一维动态内存分配，含有赋值，一元和二元加法，一元和
//二元减法，乘法等基本运算。基本用法是Array[i]。
template<class T>
class Array1D {
public:
	Array1D(int size = 0);
	Array1D(const Array1D<T>& v);
	~Array1D() {
		delete[] element;
	}
	T& operator[](int i) const;
	int Size() {
		return size;
	}
	Array1D<T>& operator=(const Array1D<T>& v);
	Array1D<T> operator+() const;
	Array1D<T> operator+(const Array1D<T>& v) const;
	Array1D<T> operator-() const;
	Array1D<T> operator-(const Array1D<T>& v) const;
	Array1D<T>& operator+=(const T& x);
	Array1D<T>& Resize(int sz);
private:
	int size;
	T*element;
};

template<class T>
Array1D<T>::Array1D(int sz) {
	size = sz;
	element = new T[sz];
}

template<class T>
Array1D<T>::Array1D(const Array1D<T>& v) {
	size = v.size;
	element = new T[size];
	for (int i = 0; i < size; i++)
		element[i] = v.element[i];
}

template<class T>
T& Array1D<T>::operator[](int i) const {
	return element[i];
}

template<class T>
Array1D<T>& Array1D<T>::operator=(const Array1D<T>& v) {
	if (this != &v) {
		size = v.size;
		delete[] element;
		element = new T[size];
		for (int i = 0; i < size; i++)
			element[i] = v.element[i];
	}
	return *this;
}

template<class T>
Array1D<T> Array1D<T>::operator-(const Array1D<T>& v) const {
	Array1D<T> w(size);
	for (int i = 0; i < size; i++)
		w.element[i] = element[i] - v.element[i];
	return w;
}

template<class T>
Array1D<T> Array1D<T>::operator-() const {
	Array1D<T> w(size);
	for (int i = 0; i < size; i++)
		w.element[i] = -element[i];
	return w;
}

template<class T>
Array1D<T> Array1D<T>::operator+(const Array1D<T>& v) const {
	Array1D<T> w(size);
	for (int i = 0; i < size; i++)
		w.element[i] = element[i] + v.element[i];
	return w;
}

template<class T>
Array1D<T> Array1D<T>::operator+() const {
	Array1D<T> w(size);
	for (int i = 0; i < size; i++)
		w.element[i] = element[i];
	return w;
}

template<class T>
Array1D<T>& Array1D<T>::operator+=(const T& x) {
	for (int i = 0; i < size; i++)
		element[i] += x;
	return *this;
}

template<class T>
Array1D<T>& Array1D<T>::Resize(int sz) {
	delete[] element;
	size = sz;
	element = new T[size];
	return *this;
}

