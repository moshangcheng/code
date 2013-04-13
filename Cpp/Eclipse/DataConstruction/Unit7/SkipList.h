//03-10-07 15:14
//跳表模板类
//跳表通常含有一个头节点和一个尾节点,0级链包含所有元素的有序链表,
//设0级链最多有n个元素,则链最大的级数为 ┗log(1/p)n┛ ,插入元素时，
//随机为新元素分配级，但删除元素时，无法控制其结构

#include <math.h>
const int maxrand = 1000;
template<class E, class K> class SkipList;

template<class E, class K>
class SkipNode {
private:
	friend class SkipList<E, K> ;
	SkipNode(int size) {
		link = new SkipNode<E, K>*[size];
	}
	~SkipNode() {
		delete[] link;
	}
	E data;
	SkipNode<E, K>** link;
};

template<class E, class K>
class SkipList {
public:
	SkipList(K Large, int MaxE = 10000, float p = 0.5);
	~SkipList();
	bool Search(const K& k, E& e) const;
	SkipList<E, K>& Insert(const E& e);
	SkipList<E, K>& Delete(const K& k, E& e);
	void Output(ostream&) const;
private:
	int Level();
	SkipNode<E, K>* SaveSearch(const K& k);
	int MaxLevel;//所允许的最大级数
	int Levels;//当前非空链的个数
	int CutOff;//用于分配级号
	K TailKey;//一个很大的值
	SkipNode<E, K>* head;//头节点指针
	SkipNode<E, K>* tail;//尾节点指针
	SkipNode<E, K>** last;//指针数组
};

template<class E, class K>
SkipList<E, K>::SkipList(K Large, int MaxE, float p) {
	CutOff = int(p * maxrand);
	MaxLevel = int(log(MaxE) / log(1 / p));
	TailKey = Large;
	Levels = 0;

	head = new SkipNode<E, K> (MaxLevel + 1);
	tail = new SkipNode<E, K> (1);
	last = new SkipNode<E, K>*[MaxLevel + 1];
	tail->data = Large;

	for (int i = 0; i <= MaxLevel; i++)
		head->link[i] = tail;
}

template<class E, class K>
SkipList<E, K>::~SkipList() {
	SkipNode<E, K>*next;
	while (head != tail) {
		next = head->link[0];
		delete head;
		head = next;
	}
	delete tail;
	delete[] last;
}

template<class E, class K>
bool SkipList<E, K>::Search(const K& k, E& e) const {
	if (k >= TailKey)
		return false;
	SkipNode<E, K>* p = head;
	for (int i = Levels; i > -1; i--)
		while (p->link[i]->data < k)
			p = p->link[i];
	e = p->link[0]->data;
	return (e == k);
}

template<class E, class K>
SkipNode<E, K>* SkipList<E, K>::SaveSearch(const K& k) {
	SkipNode<E, K>* p = head;
	for (int i = Levels; i > -1; i--) {
		while (p->link[i]->data < k)
			p = p->link[i];
		last[i] = p;
	}
	return (p->link[0]);
}

template<class E, class K>
int SkipList<E, K>::Level() {
	int lev = 0;
	while ((rand() % maxrand) <= CutOff)
		lev++;
	return (lev <= MaxLevel) ? lev : MaxLevel;
}

template<class E, class K>
SkipList<E, K>& SkipList<E, K>::Insert(const E& e) {
	K k = e;
	SkipNode<E, K> *p = SaveSearch(k);
	int lev = Level();
	if (lev > Levels) {
		lev = ++Levels;
		last[lev] = head;
	}
	SkipNode<E, K> *y = new SkipNode<E, K> (lev + 1);
	y->data = e;
	for (int i = 0; i <= lev; i++) {
		y->link[i] = last[i]->link[i];
		last[i]->link[i] = y;
	}
	return *this;
}

template<class E, class K>
SkipList<E, K>& SkipList<E, K>::Delete(const K& k, E& e) {
	SkipNode<E, K>* p = SaveSearch(k);
	for (int i = 0; i <= Levels && last[i]->link[i] == p; i++)
		last[i]->link[i] = p->link[i];
	while (Levels > 0 && head->link[Levels] == tail)
		Levels--;
	e = p->data;
	delete p;
	return *this;
}

template<class E, class K>
void SkipList<E, K>::Output(ostream& out) const {
	SkipNode<E, K>* p = head->link[0];
	while (p != tail) {
		out << p->data;
		p = p->link[0];
	}
}

template<class E, class K>
ostream& operator<<(ostream& out, const SkipList<E, K>& x) {
	x.Output(out);
	return out;
}

