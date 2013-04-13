#include "LinkedQueue.h"

template<class T> class BinaryTree;

template<class T>
class BinaryTreeNode {
public:
	friend class BinaryTree<T> ;
	BinaryTreeNode() {
		LeftChild = RightChild = 0;
	}
	BinaryTreeNode(const T& e) {
		data = e;
		LeftChild = RightChild = 0;
	}
	BinaryTreeNode(const T& e, BinaryTreeNode<T> *l, BinaryTreeNode<T> *r) {
		data = e;
		LeftChild = l;
		RightChild = r;
	}
private:
	T data;
	BinaryTreeNode<T> *LeftChild, *RightChild;
};

template<class T>
class BinaryTree {
public:
	BinaryTree() {
		root = 0;
	}
	~BinaryTree() {
	}
	;
	bool Root(T& x) const;
	int Height() const {
		return Height(root);
	}
	bool IsEmpty() const {
		return ((root) ? false : true);
	}
	void MakeTree(const T&, BinaryTree<T>&, BinaryTree<T>&);
	void BreakTree(T&, BinaryTree<T>&, BinaryTree<T>&);
	void PreOrder(void(*Visit)(BinaryTreeNode<T>*u)) {
		PreOrder(Visit, root);
	}
	void InOrder(void(*Visit)(BinaryTreeNode<T>*u)) {
		InOrder(Visit, root);
	}
	void PostOrder(void(*Visit)(BinaryTreeNode<T>*u)) {
		PostOrder(Visit, root);
	}
	void LevelOrder(void(*Visit)(BinaryTreeNode<T>*u));
	//之所以设Preorder,Inorder等的私有函数形式，是因为其公有函数形式
	//不能满足递归调用的需要。当然也可以建立一个队列循环实现
private:
	BinaryTreeNode<T>* root;
	void PreOrder(void(*Visit)(BinaryTreeNode<T>*), BinaryTreeNode<T>*);
	void InOrder(void(*Visit)(BinaryTreeNode<T>*), BinaryTreeNode<T>*);
	void PostOrder(void(*Visit)(BinaryTreeNode<T>*), BinaryTreeNode<T>*);
	int BinaryTree<T>::Height(BinaryTreeNode<T>* t) const;
};

template<class T>
bool BinaryTree<T>::Root(T& x) const {
	if (root) {
		x = root->data;
		return true;
	} else
		return false;
}

template<class T>
void BinaryTree<T>::MakeTree(const T& element, BinaryTree<T>& left, BinaryTree<
		T>& right) {
	root = new BinaryTreeNode<T> (element, left.root, right.root);
	left.root = right.root = 0;//使其没有根节点
}

template<class T>
void BinaryTree<T>::BreakTree(T& element, BinaryTree<T>& left,
		BinaryTree<T>& right) {
	if (root)
		return;
	element = root->data;
	left.root = root->LeftChild;
	right.root = root->RightChild;
	delete root;
	root = 0;
}

template<class T>
void BinaryTree<T>::PreOrder(void(*Visit)(BinaryTreeNode<T>*u), BinaryTreeNode<
		T>* t) {
	if (t) {
		Visit(t);
		PreOrder(Visit, t->LeftChild);
		PreOrder(Visit, t->RightChild);
	}
}

template<class T>
void BinaryTree<T>::InOrder(void(*Visit)(BinaryTreeNode<T>*u),
		BinaryTreeNode<T>* t) {
	if (t) {
		InOrder(Visit, t->LeftChild);
		Visit(t);
		InOrder(Visit, t->RightChild);
	}
}

template<class T>
void BinaryTree<T>::PostOrder(void(*Visit)(BinaryTreeNode<T>*u),
		BinaryTreeNode<T>* t) {
	if (t) {
		PostOrder(Visit, t->LeftChild);
		PostOrder(Visit, t->RightChild);
		Visit(t);
	}
}

template<class T>
void BinaryTree<T>::LevelOrder(void(*Visit)(BinaryTreeNode<T>*u)) {
	LinkedQueue<BinaryTreeNode<T>*> Q;
	BinaryTreeNode<T>* t;
	t = root;
	while (t) {
		Visit(t);
		if (t->LeftChild)
			Q.Add(t->LeftChild);
		if (t->RightChild)
			Q.Add(t->RightChild);
		Q.Delete(t);
	}
}

template<class T>
int BinaryTree<T>::Height(BinaryTreeNode<T>* t) const {
	if (t == 0)
		return 0;
	int hl = Height(t->LeftChild);
	int hr = Height(t->RightChild);
	if (hl > hr)
		return ++hl;
	else
		return ++hr;
}

