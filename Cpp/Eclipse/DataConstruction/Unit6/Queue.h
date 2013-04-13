template<class T>
class Queue {
public:
Queue	(int MaxQueueSize=10);
			~Queue() {delete [] queue;}
			bool IsEmpty() const {return front==rear;}
			bool IsFull()const {
				return ((rear+1)%MaxSize==front)?1:0;}
			T First()const {return queue[(front+1)%MaxSize];}
			T Last()const {return queue[rear];}
			Queue<T>& Add(const T& x);
			Queue<T>& Delete(T& x);
		private:
			int front,rear,MaxSize;
T* queue;
};

template<class T>
Queue<T>::Queue(int MaxQueueSize)
{
MaxSize=MaxQueueSize+1;
queue=new T[MaxSize];
front=rear=0;
}

template<class T>
Queue<T>& Queue<T>::Add(const T& x)
{
rear=(rear+1)%MaxSize;queue[rear]=x;
return *this;
}

template<class T>
Queue<T>& Queue<T>::Delete(T& x)
{
front=(front+1)%MaxSize;
x=queue[front];
return *this;
}
