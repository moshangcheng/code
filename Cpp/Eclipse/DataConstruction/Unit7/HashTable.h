//线性开址寻址散列模板类
//函数映射方法是除法映射，函数形式是: f(k)=k%D
//D为除数，为散列表中桶的个数
//最坏情况下插入和搜索时间均为~N，U(n)和S(n)分别表示在一次不成功搜索和
//一次成功搜索中平均搜索的桶的个数，则有：
//               U(n)~0.5(1+1/(1-x)^2)
//               S(n)~0.5(1+1/(1-x))
//其中x为负载因子，x=n/D。
//选择D时，应使D为素数或者没有小于20的素数因子
//虽然每个元素的关键值不同，但有可能有相同的f(k)值，将下一个f(k)值相同
//的元素放在前一元素的下一个可用桶中，这种解决溢出的方法叫线性开型寻址
template<class E, class K>
class HashTable {
public:
	HashTable(int divisor = 11);
	~HashTable() {
		delete[] ht;
		delete[] empty;
	}
	bool Search(const K& k, E& e) const;
	HashTable<E, K>& Insert(const E& e);
	HashTable<E, K>& Delete(const K& k, E& e);
	void Output() const;
private:
	int hSearch(const K& k) const;
	int D;
	E* ht;
	bool *empty;
};

template<class E, class K>
HashTable<E, K>::HashTable(int divisor) {
	D = divisor;
	ht = new E[D];
	empty = new bool[D];
	for (int i = 0; i < D; i++)
		empty[i] = true;
}

//搜索关键值为k的元素时，若到达一个空桶或回到f(k)桶时，搜索失败
template<class E, class K>
int HashTable<E, K>::hSearch(const K& k) const {
	int i = k % D;
	int j = i;
	do {
		if (empty[j] || ht[j] == k)
			return j;
		j = (j + 1) % D;
	} while (j != i);
	return j;
}

template<class E, class K>
bool HashTable<E, K>::Search(const K& k, E& e) const {
	int b = hSearch(k);
	if (empty[b] || ht[b] != k)
		return false;
	e = ht[b];
	return true;
}

template<class E, class K>
HashTable<E, K>& HashTable<E, K>::Insert(const E& e) {
	K k = e;
	int b = hSearch(k);
	if (empty[b]) {
		empty[b] = false;
		ht[b] = e;
		return *this;
	}
}

//删除会带来多个元素的移动，可以从欲删除的元素开始，逐个检查每个桶
//以确定要移动的元素，知道到达一个空桶或返回欲删除的元素为止。
template<class E, class K>
HashTable<E, K>& HashTable<E, K>::Delete(const K& k, E& e) {
	int b = hSearch(k);
	if (ht[b] == k) {
		e = ht[b];
		b = (b + 1) % D;
		while (!empty[b] && ht[b] != e) {
			ht[(b - 1 + D) % D] = ht[b];
			b = (b + 1) % D;
		}
		if (empty[b])
			empty[(b - 1 + D) % D] = 1;
	}
	return *this;
}

template<class E, class K>
void HashTable<E, K>::Output() const {
	for (int i = 0; i < D; i++)
		if (empty[i] == 0)
			cout << ht[i] << endl;
}

