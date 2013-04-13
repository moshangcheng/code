/**
 * @author moshangcheng
 * @version 1.0
 * @date 2011-7-31 下午06:18:25
 * @brief map count find
 * 在常成员函数里访问对象的数据成员，会导致对象的数据成员成为常量。
 * map的count函数是常成员函数，在count里调用了PairCompare的实例的()操作符。
 * 因此，如果()操作符不是常成员，会导致编译错误。
 * 编译信息显示无法调用常量PairCompare对象的非常成员函数。
 *
 */
#include <map>
#include <algorithm>
#include <iostream>
using namespace std;


struct PairCompare {
	bool operator()(const pair<int, int>& a, const pair<int, int>& b) const {
		return a.first < b.first || (a.first == b.first && a.second < b.second);
	}
};

int main() {
	map<pair<int, int> , int, PairCompare> m;
	pair<int, int> tempKey = make_pair(3, 3);
	m[tempKey] = 4;
	m.count(tempKey);
}

