#include <iostream>

using namespace std;

class MyExBase{
    public:
        int data;
};

class MyEx: public MyExBase
{
    public:
        MyEx(int i)
        {
            data = i;
        }
};

int main()
{
    try{
        throw MyEx(1);
    }catch (const MyExBase& e){
        std::cout<<e.data<<std::endl;
    }
}

