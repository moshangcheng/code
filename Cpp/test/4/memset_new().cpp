#include <iostream>
#include <string>
using namespace std;

struct pix { int a, b; char c[3];};

int main()
{    
    int size;
    cin >> size;
    
    //整型数组的初始化 
    int* s2 = new int[size];
    cout << sizeof(s2) << endl; //sizeof(s2) = 4
    memset(s2, 0, sizeof(s2));//改为sizeof(int)*size初始化成功 
    for(int i = 0; i < size; i++) 
    cout << s2[i] << ' ';
    cout << endl << endl;
    
    cout << sizeof(pix) << endl << endl;//sizeof(pix) = 12
    
    //结构体数组的初始化 
    pix* s1 = new pix[size];
    cout << sizeof(s1) << endl; //sizeof(s1) = 4
    memset(s1, 1, sizeof(pix)*size);// sizeof(pix)*size仍然初始化失败 
    //这种初始化，字符型数组末尾不是'\0'，无法判断是否结尾 
    for(int i = 0; i < size; i++) 
    cout << s1[i].a << ' ' << s1[i].b << ' ' << s1[i].c[0] << s1[i].c[1] << s1[i].c[2] << endl;
    cout << endl;
    
    system("pause");
    return 0;    
}
