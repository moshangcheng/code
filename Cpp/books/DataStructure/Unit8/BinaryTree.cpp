//完全二叉树 若其有n个元素，则其深度为┍log2（n+1）┓ 。
//完全二叉树中有下列关系：
//1 i=1时，该元素为二叉树的根。若i>1时，则该元素的父节点编号为┗i/2┛ ；
//2 2i>n时，该元素无左孩子。否则，其左孩子的编号为2i；
//3 若2i+1>n时，该元素无右孩子。否则，其右孩子编号为2i+1；

//二叉树链表模板类

#include <iostream>
using namespace std;
#include "BinaryTree.h"

//为什么将num改成count会出现编译错误？
int num = 0;
template<class T>
void ct(BinaryTreeNode<T>* t) {
	num++;
}

int main() {
	BinaryTree<int> a, x, y, z;
	y.MakeTree(1, a, a);
	z.MakeTree(2, a, a);
	x.MakeTree(3, y, z);
	y.MakeTree(4, x, a);
	y.PreOrder(ct);
	int m;
	y.Root(m);
	cout << m << endl;
	cout << y.Height() << " " << num << endl;
	system("pause");
	return 0;
}
