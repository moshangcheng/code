#include <vector>  // STL向量的头文件。这里没有".h"。
#include <iostream>  // 包含cout对象的头文件。
using namespace std;  //保证在程序中可以使用std命名空间中的成员。

char* szHW = "Hello World";  
//这是一个字符数组，以"\0"结束。

int main(int argc, char* argv[])
{
  vector <char> vec;  //声明一个字符向量vector (STL中的数组) 

  //为字符数组定义一个游标iterator。
  vector <char>::iterator vi;

  //初始化字符向量，对整个字符串进行循环，
  //用来把数据填放到字符向量中，直到遇到"\0"时结束。
  char* cptr = szHW;  // 将一个指针指向"Hello World"字符串
  while (*cptr != '\0')
  {  vec.push_back(*cptr);  cptr++;  }
  // push_back函数将数据放在向量的尾部。

  // 将向量中的字符一个个地显示在控制台
  for (vi=vec.begin(); vi!=vec.end(); vi++)  
  // 这是STL循环的规范化的开始--通常是 "!=" ， 而不是 "<"
  // 因为"<" 在一些容器中没有定义。 
  // begin()返回向量起始元素的游标（iterator），end()返回向量末尾元素的游标（iterator）。
  {  cout << *vi;  }  // 使用运算符 "*" 将数据从游标指针中提取出来。
  cout << endl;  // 换行

  system("pause");
  return 0;
}


