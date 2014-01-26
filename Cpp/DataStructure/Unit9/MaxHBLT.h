//高度优先左高树：当且仅当一颗二叉树得任何一个内部节点，其左孩子的s值
//大于等于右孩子的s值时，称其为 HBLT
//定理：1) 以x为根得子树的节点数目至少为2^s(x)-1
//      2) 若子树x有m个节点，s(x)最多为log2(m+1)
//      3) 通过最右路径从x到达外部节点的路径长度为s(x)
//类似的还有重量优先左高树 WBLT
//最大 HBLT模板类
#include "Queue.h"
template<class T> class MaxHBLT;
template<class T>
void swap(T& a, T& b) {
	T c = a;
	a = b;
	b = c;
}

template<class T>
class HBLTNode {
	friend class MaxHBLT<T> ;
public:
	HBLTNode(const T& e, const int sh) {
		data = e;
		s = sh;
		LeftChild = RightChild = 0;
	}
private:
	int s;
	T data;
	HBLTNode<T>* LeftChild, *RightChild;
};

template<class T>
class MaxHBLT {
public:
	MaxHBLT() {
		root = 0;
	}
	~MaxHBLT() {
		Free(root);
	}
	T Max() {
		return root->data;
	}
	MaxHBLT<T>& Insert(const T& x);
	MaxHBLT<T>& DeleteMax(T& x);
	MaxHBLT<T>& Meld(MaxHBLT<T>& x) {
		Meld(root, x.root);
		x.root = 0;
		return *this;
	}
	void Initialize(T a[], int n);
private:
	void Free(HBLTNode<T>* t);
	void Meld(HBLTNode<T>* x, HBLTNode<T>* y);
	HBLTNode<T>* root;
};

template<class T>
void MaxHBLT<T>::Meld(HBLTNode<T>* x, HBLTNode<T>* y) {
	if (!x) {
		x = y;
		return;
	}
	if (x->data < y->data)
		Swap(x, y);
	Meld(x->RightChild, y);
	if (!x->LeftChild) {
		x->LeftChild = x->RightChild;
		x->RightChild = 0;
		x->s = 1;
	} else {
		if (x->LeftChild->s < x->RightChild->s)
			Swap(x->LeftChild, x->RightChild);
		x->s = x->RightChild->s + 1;
	}
}

template<class T>
MaxHBLT<T>& MaxHBLT<T>::DeleteMax(T& x) {
	x = root->data;
	HBLTNode<T>* L = root->LeftChild;
	HBLTNode<T>* R = root->RightChild;
	delete root;
	root = L;
	Meld(root, R);
	return *this;
}

template<class T>
void MaxHBLT<T>::Initialize(T a[], int n) {
	Queue<HBLTNode<T>*> Q(n);//节省存储空间
	Free(root);
	for (int i = 1; i <= n; i++) {
		HBLTNode<T>* q = new HBLTNode<T> (a[i], 1);
		Q.Add(q);
	}
	HBLTNode<T> *b, *c;
	for (int i = 1; i <= n - 1; i++) {
		Q.Delete(b).Delete(c);
		Meld(b, c);
		Q.Add(b);
	}
	if (n)
		Q.Delete(root);
}

template<class T>
MaxHBLT<T>& MaxHBLT<T>::Insert(const T& x) {
	HBLTNode<T>* q = new HBLTNode<T> (x, 1);
	Meld(root, q);
	return *this;
}

