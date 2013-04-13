template<class T> class Chain;
template<class T> class ChainIterator;

template<class T>
class ChainNode{
    public:
        friend class Chain<T>;
        friend class ChainIterator<T>;
    private:
        T data;
        ChainNode<T>* link;
};

template <class T>
class Chain{
    public:
        friend class ChainIterator<T>;
        Chain() { first=0;}
        ~Chain();
        bool IsEmpty() const { return first==0; }
        int Length()const;
        bool Find(int k,T &x)const;
        int Search(const T& x)const;
        Chain<T>& Delete(int k,T& x);
        Chain<T>& Insert(int k,const T& x);
        void Output(ostream& out)const;
        void Erase();
        Chain<T>& Append(const T& x);
        void Zero() {first=0; }
    private:
        ChainNode<T> *first,*last;
};

template <class T>
void Chain<T>::Erase()
{
    ChainNode<T>* next;
    while(first){
        next=first->link;
        delete first;
        first=next;
    }
}

template<class T>
Chain<T>::~Chain()
{
    Erase();
}

template<class T>
int Chain<T>::Length() const
{
    ChainNode<T>* current=first;
    int len=0;
    while(current){
        len++;
        current=current->link;
    }
    return len;
}

template<class T>
bool Chain<T>::Find(int k,T &x) const
{
    if(k<1) return false;
    ChainNode<T>* current=first;
    int index=1;
    while(index<k&&current){
        current=current->link;
        index++;
    }
    if(current) { x=current->data; return true; }
    return false;
}

template<class T>
int Chain<T>::Search(const T& x)const
{
    ChainNode<T>* current=first;
    int index=1;
    while(current&&current->data!=x){
        current=current->link;
        index++;
    }
    if(current) return index;
    return 0;
}

template <class T>
void Chain<T>::Output(ostream& out)const
{
    ChainNode<T>* current;
    for(current=first;current;current=current->link)
    out<<current->data<<" ";
}

template<class T>
ostream& operator<<(ostream& out,const Chain<T>& x)
{
    x.Output(out); return out;
}

template<class T>
Chain<T>& Chain<T>::Delete(int k,T& x)
{
    ChainNode<T>* p=first;
    if(k==1) first=first->link;
    else{
        ChainNode<T>* q=first;
        for(int index=1;index<k-1&&q;index++) q=q->link;
        p=q->link;
        if(p==last) last=q;
        q->link=p->link;
    }
    x=p->data;
    delete p;
    return *this;
}

template<class T>
Chain<T>& Chain<T>::Insert(int k,const T& x)
{
    ChainNode<T>* p=first;
    for(int index=1;index<k&&p;index++) p=p->link;
    ChainNode<T> *y=new ChainNode<T>;
    y->data=x;
    if(k){
        y->link=p->link;
        p->link=y;
    }
    else{
        y->link=first;
        first=y;
    }
    if(!y->link) last=y;
    return *this;
}

template<class T>
class ChainIterator{
    public:
        T* Initialize(const Chain<T>& c){
            location=c.first;
            if(location) return &location->data;
            return 0;
        }
        T* Next(){
            if(!location) return 0;
            location=location->link;
            if(location) return &location->data;
            return 0;
        }
        private:
            ChainNode<T> *location;
};

template<class T>
Chain<T>& Chain<T>::Append(const T& x)
{
    ChainNode<T>* y;
    y=new ChainNode<T>;
    y->data=x;y->link=0;
    if(first){
        last->link=y;
        last=y;
    }
    else first=last=y;
    return *this;
}

