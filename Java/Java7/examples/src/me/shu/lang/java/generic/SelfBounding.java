package me.shu.lang.java.generic;

// https://www.artima.com/weblogs/viewpost.jsp?thread=136394

class SelfBounded<T extends SelfBounded<T>> {
	T element;

	SelfBounded<T> set(T arg) {
		element = arg;
		return this;
	}

	T get() {
		return element;
	}
}

class A extends SelfBounded<A> {
	String name = "abc";
}

class B extends SelfBounded<A> {
} // Also OK

class C extends SelfBounded<C> {
	C setAndGet(C arg) {
		set(arg);
		return get();
	}
}

class D {
}

// Can't do this:
// class E extends SelfBounded<D> {}
// Compile error: Type parameter D is not within its bound

public class SelfBounding {
	public static void main(String[] args) {
		A a = new A();
		a.set(a);
		a.set(new A());
		a = a.set(new A()).get();
		a = a.get();
		C c = new C();
		c = c.setAndGet(new C());
	}
}