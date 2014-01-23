//竞赛树支持的基本操作是替换最大（最小）元素，操作开销是logn,
//虽然利用堆和左高树也能获得同样复杂度,但它们都不能实现可预见的断接操作
//所以当需要按照指定的方式断开连接，例如选择最先插入的元素，或选择左端
//元素时，可选择竞赛树这种数据结构
//对于赢者树的Replay操作，在许多应用当中，往往是赢者被新的选手取代，
//因此，从取代赢者的外部节点到根节点的路径上的所有比赛都有重新进行
//如果在每个内部节点中记录的是该节点比赛的输者而不是赢者，那么当e[i]
//发生变化时，能够减少确定比赛选手的工作量
//因此，使用输者树能简化一个赢者发生变化后重新比赛的过程，但它并不
//简化其他选手发生变化时的情况
//函数Winner(a,b,c)返回的是a[b]和a[c]比赛的赢者，定义不同的Winner,
//可以构造最小赢者树或最大赢者树
template<class T>
class WinnerTree {
public:
	WinnerTree(int TreeSize = 10);
	~WinnerTree() {
		delete[] t;
	}
	void Initialize(T*a, int size, int(*winner)(T*a, int b, int c));
	int Winner() const {
		return (n) ? t[1] : 0;
	}
	int Winner(int i) const {
		return (i < n) ? t[i] : 0;
	}
	void Replay(int i, int(*winner)(T*a, int b, int c));
private:
	int MaxSize;
	int n;//外部节点数为n时，内部节点数为n-1
	int LowExt;//最底层的外部节点
	int offset;
	int* t;//赢者树数组
	T* e;//外部元素数组
	void Play(int p, int lc, int rc, int(*winner)(T*a, int b, int c));
};

template<class T>
WinnerTree<T>::WinnerTree(int TreeSize) {
	MaxSize = TreeSize;
	t = new int[MaxSize];
	n = 0;
}

template<class T>
void WinnerTree<T>::Initialize(T*a, int size, int(*winner)(T*a, int b, int c)) {
	n = size;
	e = a;//此处的a[]必须把a[1]设定为第一个元素
	int i, s;//s为内部节点的最底层的第一个元素
	for (s = 1; 2 * s <= n - 1; s += s)
		;//计算s的大小
	LowExt = 2 * (n - s);
	offset = 2 * s - 1;//从第一层到内部节点最底层的 节点数总数
	//最底层外部节点的比赛
	for (i = 2; i <= LowExt; i += 2)
		Play((offset + i) / 2, i - 1, i, winner);
	//其余外部节点的比赛
	if (n % 2) {//n为奇数时，内部节点和外部节点比赛
		Play(n / 2, t[n - 1], LowExt + 1, winner);
		i = LowExt + 3;
	} else
		i = LowExt + 2;
	for (; i <= n; i += 2)
		Play((i - LowExt + n - 1) / 2, i - 1, i, winner);
}

//函数Play在节点t[p]处进行比赛，然后沿赢者树不断上升，直到左孩子
//p是lc和rc的父节点，对于不同的外部节点，其父节点表达形式不同
template<class T>
void WinnerTree<T>::Play(int p, int lc, int rc, int(*winner)(T*a, int b, int c)) {
	t[p] = winner(e, lc, rc);
	while (p > 1 && p % 2) {
		t[p / 2] = winner(e, t[p - 1], t[p]);
		p /= 2;
	}
}

template<class T>
void WinnerTree<T>::Replay(int i, int(*winner)(T*a, int b, int c)) {
	int p, lc, rc, tp;
	if (i <= LowExt) {
		p = (offset + i) / 2;
		lc = 2 * p - offset;
		rc = lc + 1;
	} else {
		p = (i - LowExt + n - 1) / 2;
		if (2 * p == n - 1) {//内部节点与外部节点的比赛
			lc = t[2 * p];
			rc = i;
		} else {
			lc = 2 * p - n + 1 + LowExt;
			rc = lc + 1;
		}
	}
	tp = winner(e, lc, rc);
	//if(tp==t[p]) return;//当一次比赛的赢者与上一次该比赛的赢者相同时
	//可以不再进行比赛
	t[p] = tp;
	p /= 2;
	for (; p > 0; p /= 2) {
		if (2 * p < n - 1)
			tp = winner(e, t[2 * p], t[2 * p + 1]);
		else
			tp = winner(e, t[2 * p], LowExt + 1);
		//if(t[p]==tp) break;
		t[p] = tp;
	}
}

