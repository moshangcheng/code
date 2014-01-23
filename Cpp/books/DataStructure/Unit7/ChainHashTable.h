template<class E, class K> class SortedChain;

template<class E, class K>
class SortedChainNode {
private:
	friend class SortedChain<E, K> ;
	E data;
	K key;
	SortedChainNode<E, K>* link;
};

template<class E, class K>
class SortedChain {
public:
	SortedChain() {
		first = 0;
	}
	~SortedChain();
	bool IsEmpty() const {
		return first == 0;
	}
	int Length() const;
	bool Search(const K& k, E& e) const;
	void Output(ostream& out) const;
	SortedChain<E, K>& Delete(const K& k, E& e);
	SortedChain<E, K>& Insert(const E& e);
	SortedChain<E, K>& DistinctInsert(const E& e);
private:
	SortedChainNode<E, K>* first;
};

template<class E, class K>
SortedChain<E, K>::~SortedChain() {
	SortedChainNode<E, K>* p;
	while (first) {
		p = first->link;
		delete first;
		first = p;
	}
}

template<class E, class K>
int SortedChain<E, K>::Length() const {
	int len = 0;
	SortedChainNode<E, K>* cr = first;
	while (cr) {
		cr = cr->link;
		len++;
	}
	return len;
}

template<class E, class K>
void SortedChain<E, K>::Output(ostream& out) const {
	SortedChainNode<E, K>* cr = first;
	while (cr) {
		out << cr->data << " ";
		cr = cr->link;
	}
}

template<class E, class K>
bool SortedChain<E, K>::Search(const K& k, E& e) const {
	SortedChainNode<E, K>* p = first;
	for (; p && p->data < k; p = p->link)
		;
	if (p && p->data == k) {
		e = p->data;
		return true;
	}
	return false;
}

template<class E, class K>
SortedChain<E, K>& SortedChain<E, K>::Delete(const K& k, E& e) {
	SortedChainNode<E, K>* p = first, *tp = 0;
	for (; p && p->data < k; tp = p, p = p->link)
		;
	if (p && p->data == k) {
		e = p->data;
		if (tp)
			tp->link = p->link;
		else
			first = p->link;
		delete p;
		return *this;
	}
}

template<class E, class K>
SortedChain<E, K>& SortedChain<E, K>::DistinctInsert(const E& e) {
	SortedChainNode<E, K>* p = first, *tp = 0;
	for (; p && p->data < e; tp = p, p = p->link)
		;
	SortedChainNode<E, K>* q = new SortedChainNode<E, K> ;
	q->data = e;
	q->link = p;
	if (tp)
		tp->link = q;
	else
		first = q;
	return *this;
}

template<class E, class K>
ostream& operator<<(ostream& out, const SortedChain<E, K>& x) {
	x.Output(out);
	return out;
}

template<class E, class K>
class ChainHashTable {
public:
	ChainHashTable(int divisor = 11) {
		D = divisor;
		ht = new SortedChain<E, K> [D];
	}
	~ChainHashTable() {
		delete[] ht;
	}
	bool Search(const K& k, E& e) const {
		return ht[k % D].Search(k, e);
	}
	ChainHashTable<E, K>& Insert(const E& e) {
		ht[e % D].DistinctInsert(e);
		return *this;
	}
	ChainHashTable<E, K>& Delete(const K& k, E& e) {
		ht[k % D].Delete(k, e);
		return *this;
	}
	void Output(ostream&) const;
private:
	int D;
	SortedChain<E, K>* ht;
};

template<class E, class K>
void ChainHashTable<E, K>::Output(ostream& out) const {
	for (int i = 0; i < D; i++)
		out << ht[i] << endl;
}

template<class E, class K>
ostream& operator<<(ostream& out, const ChainHashTable<E, K>& x) {
	x.Output(out);
	return out;
}

