#include <iostream>
#include <string>
using namespace std;

class demo
{
public:
	~demo()
	{
		cout<<"destructed"<<endl;
	}
	int _int;
};

int main()
{
	demo *ptDM = new demo[10];
	int *pti = (int*)ptDM;
	cout<<*(pti - 1)<<endl;
	delete [] ptDM;
	return 0;
}