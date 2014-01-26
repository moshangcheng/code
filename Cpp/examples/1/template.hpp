template<class T>
class TemplateClass {
public:
    T* mp;
    TemplateClass(T* ip = 0);
    void Run() {
        mp->Run();
    }
};

template<class T>
TemplateClass<T>::TemplateClass(T* ip)
{
    Run();
}


