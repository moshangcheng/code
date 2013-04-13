//20-09-07 13:03
//模板稀疏矩阵类LinkedMatrix，链表存储，含有转置，二元加法，赋值 ,
//二元减法等基本运算。

#include "Chain.h"

template<class T> class LinkedMatrix;
template<class T> class HeadNode;

template<class T>
class CNode {
public:
	friend class HeadNode<T> ;
	friend class LinkedMatrix<T> ;
	int operator!=(const CNode<T>& y) {
		return value != y.value;
	}
	void Output(ostream& out) const {
		out << " column " << col << " value " << value;
	}
private:
	int col;
	T value;
};

template<class T>
ostream& operator<<(ostream& out, const CNode<T>& x) {
	x.Output(out);
	out << endl;
	return out;
}

template<class T>
class HeadNode {
public:
	friend class LinkedMatrix<T> ;
	int operator!=(const HeadNode<T>& x) {
		return row != x.row;
	}
	void Output(ostream& out) const {
		out << " row " << row;
	}
private:
	int row;
	Chain<CNode<T> > a;
};

template<class T>
ostream& operator<<(ostream& out, const HeadNode<T>& x) {
	x.Output(out);
	out << endl;
	return out;
}

template<class T>
class LinkedMatrix {
public:
	void Input(istream&);
	void Output(ostream&) const;
	LinkedMatrix() {
	}
	~LinkedMatrix() {
	}
	void Transpose(LinkedMatrix<T>& b) const;
private:
	int rows, cols;
	Chain<HeadNode<T> > a;
};

template<class T>
void LinkedMatrix<T>::Input(istream& in) {
	a.Erase();
	int terms;
	cout << "Enter number of rows,columns,and terms " << endl;
	in >> rows >> cols >> terms;
	HeadNode<T> H;
	H.row = 0;
	for (int i = 1; i <= terms; i++) {
		cout << "Enter row,column,and value of term " << i << endl;
		int row, col;
		T value;
		in >> row >> col >> value;
		if (row > H.row) {
			if (H.row)
				a.Append(H);
			H.row = row;
			H.a.Zero();
		}
		CNode<T>*c = new CNode<T> ;
		c->col = col;
		c->value = value;
		H.a.Append(*c);
	}
	if (H.row)
		a.Append(H);
	H.a.Zero();
}

template<class T>
void LinkedMatrix<T>::Output(ostream& out) const {
	ChainIterator<HeadNode<T> > p;
	out << " rows= " << rows << " columns= " << cols << endl;
	HeadNode<T>*h = p.Initialize(a);
	if (!h) {
		out << "No non-zero terms\n";
		return;
	}
	while (h) {
		out << " row " << h->row << endl;
		out << h->a << endl;
		h = p.Next();
	}
	return;
}

template<class T>
void LinkedMatrix<T>::Transpose(LinkedMatrix<T>& b) const {
	b.a.Erase();
	Chain<CNode<T> >*bin;
	bin = new Chain<CNode<T> > [cols + 1];
	ChainIterator<HeadNode<T> > p;
	HeadNode<T>*h = p.Initialize(a);
	while (h) {
		int r = h->row;
		ChainIterator<CNode<T> > q;
		CNode<T>* z = q.Initialize(h->a);
		CNode<T> x;
		x.col = r;
		while (z) {
			x.value = z->value;
			bin[z->col].Append(x);
			z = q.Next();
		}
		h = p.Next();
	}
	b.rows = cols;
	b.cols = rows;
	HeadNode<T> H;
	for (int i = 1; i <= cols; i++)
		if (!bin[i].IsEmpty()) {
			H.row = i;
			H.a = bin[i];
			b.a.Append(H);
			bin[i].Zero();
		}
	H.a.Zero();
	delete[] bin;
}

template<class T>
ostream& operator<<(ostream& out, const LinkedMatrix<T>& x) {
	x.Output(out);
	return out;
}

template<class T>
istream& operator>>(istream& in, LinkedMatrix<T>& x) {
	x.Input(in);
	return in;
}

