//最大树是指每个节点的值都大于或等于其子节点的值的树
//最大堆是指最大完全二叉树
//堆结构是一种隐式的数据结构,用完全二叉树表示的堆在数组中是隐式存储的
//没有明确的指针或数据能重构这种结构，由于没有存储结构信息，这种方法
//空间利用率很高，但需要合并两个优先队列或多个长度不同的队列时，
//它不能满足要求
template<class T>
class MaxHeap {
public:
	MaxHeap(int MaxHeapSize = 10);
	~MaxHeap() {
		delete[] heap;
	}
	int Size() const {
		return CurrentSize;
	}
	T Max() {
		return heap[1];
	}
	MaxHeap<T>& Insert(const T& x);
	MaxHeap<T>& DeleteMax(T& x);
	void Initialize(T a[], int size, int ArraySizep);
	void Deactivate();
private:
	int CurrentSize, MaxSize;
	T* heap;
};

template<class T>
MaxHeap<T>::MaxHeap(int MaxHeapSize) {
	MaxSize = MaxHeapSize;
	heap = new T[MaxSize + 1];
	CurrentSize = 0;
}

template<class T>
MaxHeap<T>& MaxHeap<T>::Insert(const T& x) {
	int i = ++CurrentSize;
	while (i != 1 & x > heap[i / 2]) {
		heap[i] = heap[i / 2];
		i /= 2;
	}
	heap[i] = x;
	return *this;
}

template<class T>
MaxHeap<T>& MaxHeap<T>::DeleteMax(T& x) {
	x = heap[1];
	T y = heap[CurrentSize--];
	int i = 1, ci = 2;
	while (ci <= CurrentSize) {
		//heap[ci]应是i较大的孩子
		if (ci < CurrentSize && heap[ci] < heap[ci + 1])
			ci++;
		if (y >= heap[ci])
			break;
		heap[i] = heap[ci];
		i = ci;
		ci *= 2;
	}
	heap[i] = y;
	return *this;
}

//初始化函数的复杂性为O(n)
template<class T>
void MaxHeap<T>::Initialize(T a[], int size, int ArraySize) {
	delete[] heap;
	heap = a;//此处的a[]的第一个元素是a[1]
	CurrentSize = size;
	MaxSize = ArraySize;
	for (int i = CurrentSize / 2; i > 0; i--) {
		T y = heap[i];
		int c = 2 * i;
		while (c <= CurrentSize) {
			if (c < CurrentSize && heap[c] < heap[c + 1])
				c++;
			if (y >= heap[c])
				break;
			heap[c / 2] = heap[c];
			c *= 2;
		}
		heap[c / 2] = y;
	}
}

template<class T>
void MaxHeap<T>::Deactivate() {
	heap = NULL;
}

