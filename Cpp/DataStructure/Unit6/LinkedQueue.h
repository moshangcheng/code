template<class T> class LinkedQueue;

template<class T>
class Node {
public:
	friend class LinkedQueue<T> ;
p
rivate:
T data;
Node<T>* link;
};
template<class T>
class LinkedQueue {
public:
	LinkedQueue() {front=rear=0;}
	~LinkedQueue();
	bool IsEmpty()const {return front?false:true;}
	T First()const;
	T Last() const;
	LinkedQueue<T>& Add(const T& x);
	LinkedQueue<T>& Delete(T& x);
private:
	Node<T>*front;
	Node<T>*rear;
};

template<class T>
LinkedQueue<T>::~LinkedQueue()
{
	Node<T>*next;
	while(front) {
		next=front->link;
		delete front;
		front=next;
	}
}

template<class T>
T LinkedQueue<T>::First()const {return front->data;}

template<class T>
T LinkedQueue<T>::Last()const {return rear->data;}

template<class T>
LinkedQueue<T>& LinkedQueue<T>::Add(const T& x)
{
	Node<T>* p=new Node<T>;
	p->data=x;
	p->link=0;
	if(front) rear->link=p;
	else front=p;
	rear=p;
	return *this;
}

template<class T>
LinkedQueue<T>& LinkedQueue<T>::Delete(T& x)
{
	x=front->data;
Node<T>* p=front;
front=front->link;
delete p;
return *this;
}
