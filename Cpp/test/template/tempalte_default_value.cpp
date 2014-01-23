class A;

template<class T>
class TemplateClass {
public:
	T* mp;
	TemplateClass() {
		mp->Run();
	}
	void Run(T* ip) {
		ip->Run();
	}
};

class C {
public:
	TemplateClass<A> lTA;
	C() {}
};

class A {
public:
	void Run() {
	}
};

int main() {
	return 0;
}
