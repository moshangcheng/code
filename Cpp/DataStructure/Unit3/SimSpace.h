template<class T> class SimSpace;
template<class T> class SimChain;
template<class T>
class SimNode {
public:
	friend class SimChain<T> ;
	friend class SimSpace<T> ;
private:
	T data;
	int link;
};

template<class T>
class SimSpace {
public:
	friend class SimChain<T> ;
	SimSpace(int MaxSpaceSize = 100);
	~SimSpace() {
		delete[] node;
	}
	int Allocate();
	void Deallocate(int& i);
private:
	int NumberOfNodes, first;
	SimNode<T>*node;
};

template<class T>
SimSpace<T>::SimSpace(int MaxSpaceSize) {
	NumberOfNodes = MaxSpaceSize;
	node = new SimNode<T> [NumberOfNodes];
	for (int i = 0; i < NumberOfNodes - 1; i++)
		node[i].link = i + 1;
	node[NumberOfNodes - 1].link = -1;
	first = 0;
}

template<class T>
int SimSpace<T>::Allocate() {
	int i = first;
	first = node[first].link;
	return i;
}

template<class T>
void SimSpace<T>::Deallocate(int& i) {
	node[i].link = first;
	first = i;
	i = -1;
}

