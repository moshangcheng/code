/**
 * @author moshangcheng
 * @version 1.0
 * @date 2011-8-23 上午10:51:46
 * @brief  C++必知必会 条款6 数组形参
 * 数组作为函数参数时，数组的大小必须以某种方式加以明确，或以单独的函数参数传入，
 * 或在数组内部存在结束符。
 */

#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;

//使用指针代替数组形参，缺点是混淆了数组地址与单个元素指针
void arrayParam1(int* array, int n) {
	for(int i = 0; i < n; i++) {
		cout << array[i] << " ";
	}
	cout << endl;
}

//传递数组参数的传统方法
void arrayParam2(int array[], int n) {
	for(int i = 0; i < n; i++) {
		cout << array[i] << " ";
	}
	cout << endl;
}

//数组大小已知且大小非常重要时
//a是一个指向int[3]数组的引用
void arrayParam3(int(&array)[3]) {
	for(int i = 0; i < 3; i++) {
		cout << array[i] << " ";
	}
	cout << endl;
}

//使用模板，编译器推导数组大小
template<int n>
void arrayParam4(int(&array)[n]) {
	for(int i = 0; i < n; i++) {
		cout << array[i] << " ";
	}
	cout << endl;
}

//多维数组除第一维外的其它维边界均不退化
void arrayParam2D(int array[][20]);

//多维数组使用模板
template<int m, int n>
void arrayParam2D1(int (&array)[m][n]);

int main() {
	int intArray[] = { 1, 2, 3 };
	arrayParam1(intArray, 3);
	arrayParam2(intArray, 3);
	arrayParam3(intArray);
	arrayParam4(intArray);
	int* intPointer = new int[3];
	intPointer[0] = 4;
	intPointer[1] = 5;
	intPointer[2] = 6;
	arrayParam1(intPointer, 3);
	arrayParam2(intPointer, 3);
	//arrayParam3(intPointer);//编译错误，无法使用int*初始化int(&)[3]类型的参数
	//arrayParam4(intPointer);//编译错误，无法使用int*初始化int(&)[]类型的参数
	return 0;
}
