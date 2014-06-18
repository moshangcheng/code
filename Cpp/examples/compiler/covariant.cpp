#include <memory>
using namespace std;

template<typename T> class tpl {};

class base {
public:
	virtual tpl<base> copy() const
	{
		return tpl<base>();
	}

};

class inherit: public base {
public:
	virtual tpl<base> copy() const
	{
		return tpl<inherit>();
	}
};

int main()
{
	return 0;
}
