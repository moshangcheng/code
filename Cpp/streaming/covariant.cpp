/*
http://stackoverflow.com/questions/15815038/why-cant-shared-ptr-resolve-inheritance-relationships-in-function-interface
http://blog.bitfoc.us/?p=490
*/

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