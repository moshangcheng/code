/**
 * @author moshangcheng
 * @version 1.0
 * @date 2011-3-25 下午06:49:28
 * @brief http://acm.hdu.edu.cn/showproblem.php?pid=2848
 */
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <fstream>
#include <iostream>
using namespace std;

int main() {
	ofstream out("in.txt");
	int dataSize;
	cout << "请输入需要产生的数据集大小:\n";
	cin >> dataSize;
	srand(time(NULL));
	for (int i = 0; i < dataSize; i++) {
		long long randNum = rand();
		randNum = randNum * RAND_MAX + rand();
		randNum = randNum * RAND_MAX + rand();
		randNum = randNum * RAND_MAX + rand();
		out << randNum << " " << rand() % ((int) ceil(log10(randNum)) - 2) + 2
				<< endl;
	}
}
