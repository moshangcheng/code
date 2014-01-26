/**
 * @author moshangcheng
 * @version 1.0
 * @date 2011-8-24 上午09:48:04
 * @brief
 * 1. enum的值的数值默认从0开始
 * 2. 某个值的数值若没有指定，则为前一个值的数值加1
 * 3. enum值不属于enum，而属于enum所在的作用域，也就是说enum值和enum类型是同级的
 * 4. 可以使用命名空间包裹enum来保护全局空间，或将enum定义于类中
 * 5. enum的值不必唯一，也就是说同一个enum的不同值可以具有相同的数值。
 *    因为enum的值不属于enum，所以同一个enum的不同值数值相同和不同enum的值数值相同，
 *    两种情形是完全等价的。
 */

#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;

namespace enumSpace {
	enum Language { C = 0, Cpp, Java };
	enum IDE { VS = 0, Eclipse};
	enum UnUnique { A = 0, B = 0};
}

bool isSupported(enumSpace::IDE ide, enumSpace::Language lang) {
	if(ide == enumSpace::Eclipse) {
		return true;
	} else if(lang == enumSpace::Cpp || lang == enumSpace::C) {
		return true;
	} else {
		return false;
	}
}

int main() {
	enumSpace::Language lang = enumSpace::C;
	enumSpace::IDE ide = enumSpace::VS;
	cout << isSupported(ide, lang);
	return 0;
}
