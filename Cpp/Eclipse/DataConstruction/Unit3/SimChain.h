#include "SimSpace.h"

template<class T>
class SimChain {
public:
	SimChain() {
		first = -1;
	}
	~SimChain() {
		Destroy();
	}
	void Destroy();
	int Length() const;
	bool Find(int k, T& x) const;
	int Search(const T& x) const;
	SimChain<T>& Delete(int k, T& x);
	SimChain<T>& Insert(int k, const T& x);
	void Output(ostream& out) const;
private:
	int first;
	SimSpace<T> S;
};

template<class T>
void SimChain<T>::Destroy() {
	int next;
	while (first != -1) {
		next = S.node[first].link;
		S.Deallocate(first);
		first = next;
	}
}

template<class T>
int SimChain<T>::Length() const {
	int current = first;
	int len = 0;
	while (current != -1) {
		current = S.node[current].link;
		len++;
	}
	return len;
}

template<class T>
bool SimChain<T>::Find(int k, T& x) const {
	if (k < 1)
		return false;
	int current = first, index = 1;
	while (index < k && current != -1) {
		current = S.node[current].link;
		index++;
	}
	if (current != -1) {
		x = S.node[current].data;
		return true;
	}
	return false;
}

template<class T>
SimChain<T>& SimChain<T>::Delete(int k, T& x) {
	int p = first;
	if (k == 1)
		first = S.node[first].link;
	else {
		int q = first;
		for (int index = 1; index < k - 1 && q != -1; index++)
			q = S.node[q].link;
		p = S.node[q].link;
		S.node[q].link = S.node[p].link;
	}
	x = S.node[p].data;
	S.Deallocate(p);
	return *this;
}

template<class T>
SimChain<T>& SimChain<T>::Insert(int k, const T& x) {
	int p = first;
	for (int index = 1; index < k && p != -1; index++)
		p = S.node[p].link;
	int y = S.Allocate();
	S.node[y].data = x;
	if (k) {
		S.node[y].link = S.node[p].link;
		S.node[p].link = y;
	} else {
		S.node[y].link = first;
		first = y;
	}
	return *this;
}

template<class T>
void SimChain<T>::Output(ostream& out) const {
	for (int current = first; current != -1; current = S.node[current].link)
		out << S.node[current].data << " ";
}

template<class T>
ostream& operator<<(ostream& out, const SimChain<T>& x) {
	x.Output(out);
	return out;
}

template<class T>
int SimChain<T>::Search(const T& x) const {
	int cnt;
	for (cnt = first; S.node[cnt].data != x && cnt != -1; cnt++)
		cnt = S.node[cnt].link;
	return cnt;
}

