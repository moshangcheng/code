//20-09-07 08:16
//模板稀疏矩阵类SparseMatrix，线形表存储，含有转置，二元加法，赋值 ,
//二元减法等基本运算。

template<class T> class SparseMatrix;
template<class T>
class Term {
private:
	friend class SparseMatrix<T> ;
	int row, col;
	T value;
};

template<class T>
class SparseMatrix {
public:
	void output(ostream& out) const;
	void input(istream& in);
	SparseMatrix(int maxTerms = 10);
	~SparseMatrix() {
		delete[] a;
	}
	void Transpose(SparseMatrix<T>&) const;
	SparseMatrix<T> operator+(const SparseMatrix<T>&) const;
	SparseMatrix<T> operator*(const SparseMatrix<T>&) const;
	SparseMatrix<T>& operator=(const SparseMatrix<T>&);
	SparseMatrix<T> operator-(const SparseMatrix<T>&) const;
private:
	void Append(const Term<T>&);
	int rows, cols;
	int terms;
	Term<T>* a;
	int MaxTerms;
};

template<class T>
SparseMatrix<T>::SparseMatrix(int maxTerms) {
	MaxTerms = maxTerms;
	a = new Term<T> [MaxTerms];
	terms = rows = cols = 0;
}

template<class T>
void SparseMatrix<T>::output(ostream& out) const {
	out << "rows= " << rows << " columns= " << cols << endl;
	out << "nonzero terms= " << terms << endl;
	for (int i = 0; i < terms; i++)
		out << "a(" << a[i].row << ',' << a[i].col << ")=" << a[i].value
				<< endl;
}

template<class T>
void SparseMatrix<T>::input(istream& in) {
	cout << "Enter number of rows,columns,and terms" << endl;
	in >> rows >> cols >> terms;
	for (int i = 0; i < terms; i++) {
		cout << "Enter row,column,and value of term " << i + 1 << endl;
		in >> a[i].row >> a[i].col >> a[i].value;
	}
}

template<class T>
void SparseMatrix<T>::Transpose(SparseMatrix<T>& b) const {
	b.cols = rows;
	b.rows = cols;
	b.terms = terms;
	int*ColSize, *RowNext;
	ColSize = new int[cols + 1];
	RowNext = new int[rows + 1];
	for (int i = 1; i <= cols; i++)
		ColSize[i] = 0;
	for (int i = 0; i < terms; i++)
		ColSize[a[i].col]++;
	RowNext[1] = 0;
	for (int i = 2; i <= cols; i++)
		RowNext[i] = RowNext[i - 1] + ColSize[i - 1];
	for (int i = 0; i < terms; i++) {
		int j = RowNext[a[i].col]++;
		b.a[j].row = a[i].col;
		b.a[j].col = a[i].row;
		b.a[j].value = a[i].value;
	}
}

template<class T>
void SparseMatrix<T>::Append(const Term<T>& t) {
	a[terms] = t;
	terms++;
}

template<class T>
SparseMatrix<T> SparseMatrix<T>::operator+(const SparseMatrix<T>& b) const {
	SparseMatrix<T> c();
	c.rows = rows;
	c.cols = cols;
	c.terms = 0;
	int ct = 0, cb = 0;
	while (ct < terms && cb < b.terms) {
		int indt = a[ct].row * cols + a[ct].col;
		int indb = b.a[cb].row * cols + b.a[cb].col;
		if (indt < indb) {
			c.Append(a[at]);
			ct++;
		} else {
			if (indt == indb) {
				if (a[ct].value + b.a[cb].value) {
					Term<T> t;
					t.row = a[ct].row;
					t.col = a[ct].col;
					t.value = a[ct].value + b.a[cb].value;
					c.Append(t);
				}
				ct++;
				cb++;
			} else {
				c.Append(b.a[cb]);
				cb++;
			}
		}
	}
	for (; ct < terms; ct++)
		c.Append(a[at]);
	for (; cb < b.terms; cb++)
		c.Append(b.a[cb]);
	return c;
}

template<class T>
SparseMatrix<T> SparseMatrix<T>::operator-(const SparseMatrix<T>& b) const {
	SparseMatrix<T> c;
	c.rows = rows;
	c.cols = cols;
	c.terms = 0;
	int ct = 0, cb = 0;
	while (ct < terms && cb < b.terms) {
		int indt = a[ct].row * cols + a[ct].col;
		int indb = b.a[cb].row * cols + b.a[cb].col;
		if (indt < indb) {
			c.Append(a[ct]);
			ct++;
		} else {
			if (indt == indb) {
				if (a[ct].value - b.a[cb].value) {
					Term<T> t;
					t.row = a[ct].row;
					t.col = a[ct].col;
					t.value = a[ct].value - b.a[cb].value;
					c.Append(t);
				}
				ct++;
				cb++;
			} else {
				Term<T> t;
				t.row = b.a[cb].row;
				t.col = b.a[cb].col;
				t.value = -b.a[cb].value;
				c.Append(t);
				cb++;
			}
		}
	}
	for (; ct < terms; ct++)
		c.Append(a[ct]);
	for (; cb < b.terms; cb++) {
		Term<T> t;
		t.row = b.a[cb].row;
		t.col = b.a[cb].col;
		t.value = -b.a[cb].value;
		c.Append(t);
	}
	return c;
}

template<class T>
SparseMatrix<T>& SparseMatrix<T>::operator=(const SparseMatrix<T>& m) {
	rows = m.rows;
	cols = m.cols;
	MaxTerms = m.MaxTerms;
	terms = m.terms;
	a = new Term<T> [MaxTerms];
	for (int i = 0; i < terms; i++)
		a[i] = m.a[i];
	return *this;
}

template<class T>
ostream& operator<<(ostream& out, const SparseMatrix<T>& x) {
	x.output(out);
	return out;
}

template<class T>
istream& operator>>(istream& in, SparseMatrix<T>& x) {
	x.input(in);
	return in;
}

