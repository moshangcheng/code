/*
 * author moshangcheng
 * date 2011-3-16 上午01:50:24
 * description vector的push_back操作比数组的赋值操作慢很多，但是访问操作并不慢
 * 相比push_back操作，创建和销毁vector的操作更浪费时间。
 * 仅仅多了1000次创建和销毁，就多花了700ms的时间，在vs2010下更是明显。
 * 在vs2010下，release模式很快，但是debug模式下vecotor的操作相当慢。
 */

#include <ctime>
#include <vector>
#include <iostream>
using namespace std;

const int SIZE = 100000;
const int MAX = 1000;

int main() {

	vector<int> testVector;
	int testArray[SIZE];
	clock_t start, finish;

	start = clock();
	for (int i = 0; i < MAX; i++) {
		testVector.clear();
		for (int j = 0; j < SIZE; j++) {
			testVector.push_back(j);
		}
	}
	finish = clock();
	cout << "循环内语句共用一个vector\n";
	cout << "大小为 " << SIZE << " 的vector进行 " << MAX << " 次push_back操作用时: "
			<< finish - start << " ms\n";

	start = clock();
	for (int i = 0; i < MAX; i++) {
		vector<int> tempVector;
		for (int j = 0; j < SIZE; j++) {
			tempVector.push_back(j);
		}
	}
	finish = clock();
	cout << "循环内语句使用各自vector\n";
	cout << "大小为 " << SIZE << " 的vector进行 " << MAX << " 次push_back操作用时: "
			<< finish - start << " ms\n";

	start = clock();
	for (int i = 0; i < MAX; i++) {
		for (int j = 0; j < SIZE; j++) {
			testArray[j] = j;
		}
	}
	finish = clock();
	cout << "大小为 " << SIZE << " 的数组进行 " << MAX << " 次赋值操作用时: " << finish
			- start << " ms\n";

	start = clock();
	for (int i = 0; i < MAX; i++) {
		for (int j = 0; j < SIZE; j++) {
			int temp = testVector[j];
		}
	}
	finish = clock();
	cout << "循环内语句共用一个vector\n";
	cout << "大小为 " << SIZE << " 的vector进行 " << MAX << " 次访问操作用时: "
			<< finish - start << " ms\n";

	start = clock();
	for (int i = 0; i < MAX; i++) {
		for (int j = 0; j < SIZE; j++) {
			int temp = testArray[j];
		}
	}
	finish = clock();
	cout << "大小为 " << SIZE << " 的数组进行 " << MAX << " 次访问操作用时: " << finish
			- start << " ms\n";

	return 0;
}
