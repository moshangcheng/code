/**
 * @author moshangcheng
 * @version 1.0
 * @date 2011-8-27 下午04:03:16
 * @brief
 */

#include <iostream>
#include <cstdio>
#include <cmath>
#include <string>
#include <typeinfo>
using namespace std;

void h(int& a, const string& s) {
	cout << s << " " << a << endl;
}

template<typename T1, typename T2, typename Result>
struct G: public binary_function<T1, T2, Result> {
	Result (*func)(T1, T2);
	G(Result(*x)(T1, T2)) :
		func(x) {
	}
	Result operator()(T1 t1, T2 t2) const {
		return func(t1, t2);
	}
};

template<typename T1, typename T2, typename Result>
G<T1, T2, Result> makeG(Result(*x)(T1, T2)) {
	return G<T1, T2, Result> (x);
}

template<typename Op>
class F {
public:
	Op op;
	typename Op::second_argument_type v;
	F(const Op& op, const typename Op::second_argument_type& v) :
		op(op), v(v) {
	}
	typename Op::result_type  f(typename Op::first_argument_type const & t) {
		return op(t, v);
	}
	typename Op::result_type f(typename Op::first_argument_type& t) {
		return op(t, v);
	}
};

class testOverload {
	void fun(int&& a) { cout << a << endl; }
	void fun(const int&& a) { cout << a << endl; }
};

template<typename Op, typename Arg>
F<Op> makeF(const Op& op, const Arg& arg) {
	return F<Op> (op, typename Op::second_argument_type(arg));
}

int main() {
	int a = 1;
	//makeG(h)(a, "G");
	//makeF(makeG(h), string("F")).f(3);
	//makeF(makeG(h), string("F")).f(a);
	return 0;
}
