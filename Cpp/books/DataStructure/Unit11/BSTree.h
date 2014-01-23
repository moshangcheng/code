#include "BinaryTree.h"

template<class T>
void Output(BinaryTreeNode<T>* t) {
	cout << t->data << " ";
}

template<class E, class K>
class BSTree: public BinaryTree<E> {
public:
	bool Search(const K& k, E& e) const;
	BSTree<E, K>& Insert(const E& e);
	BSTree<E, K>& Delete(const K& k, E& e);
	void Ascent() {
		InOrder(Output);
		cout << endl;
	}
};

template<class E, class K>
bool BSTree<E, K>::Search(const K& k, E& e) const {
	BinaryTree<E>* p = root;
	while (p) {
		if (k < p->data)
			p = p->LeftChild;
		else if (k > p->data)
			p = p->RightChild;
		else {
			e = p->data;
			return true;
		}
	}
	return false;
}

template<class E, class K>
BSTree<E, K>& BSTree<E, K>::Insert(const E& e) {
	BinaryTreeNode<E>* p = root, *pp = NULL;//pp是parent_point
	while (p) {
		pp = p;
		if (e < p->data)
			p = p->LeftChild;
		else if (e > p->data)
			p = p->RightChild;
	}
	BinaryTreeNode<E>* r = new BinaryTreeNode<E> (e);
	if (root) {
		if (e < pp->data)
			pp->LeftChild = r;
		else
			pp->RightChild = r;
	} else
		root = r;
	return *this;
}

//删除关键值为k的元素，并将其放入e 
//要删除一个左右子树都不为空的节点，只需将该元素替换为它的左子树中的
//最大元素或右子树的最小元素，一般用左子树的最大元素 
template<class E, class K>
BSTree<E, K>& BSTree<E, K>::Delete(const K& k, E& e) {
	BinaryTreeNode<E>* p = root, **p = NULL;
	while (p && p->data != k) {
		pp = p;
		if (k < p->data)
			p = p->LeftChild;
		else
			p = p->RightChild;
	}
	e = p->data;//保存欲删除的元素
	//对树进行重构，处理有两个孩子的情形
	if (p->LeftChild && p->RightChild) {
		BinaryTreeNode<E>* s = p->LeftChild, *ps = p;
		while (s->RightChild) {
			ps = s;
			s = s->RightChild;
		}
		//将最大元素从s移动到p
		p->data = s->data;
		p = s;
		pp = ps;
	}
	//删除p
	BinaryTreeNode<E>* c;
	if (p->LeftChild)
		c = p->LeftChild;
	else
		c = p->RightChild;
	if (p == root)
		root = c;
	else {
		if (p == pp->LeftChild)
			pp->LeftChild = c;
		else
			pp->RightChild = c;
	}
	delete p;
	return *this;
}

