/**
 * @author moshangcheng
 * @version 1.0
 * @date 2011-8-7 下午06:58:33
 * @brief cf 80 div2
 */
#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;

int main() {
	int n;
	while(cin >> n) {
		if(n  <= 10 || n > 21) {
			cout << 0 << endl;
		} else if(n == 20) {
			cout << 15 << endl;
		} else {
			cout << 4 << endl;
		}
	}
}
