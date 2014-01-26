/**
 * @author moshangcheng
 * @version 1.0
 * @date 2011-11-7 下午11:54:14
 * @brief http://acm.nankai.edu.cn/p1772.html
 */

#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <vector>
using namespace std;

int num[26];

int main() {
	string input;
	fill(num, num + 26, 0);
	for (int i = 0; i < 4; i++) {
		getline(cin, input, '\n');
		for (int j = 0; j < input.size(); j++) {
			if (input[j] <= 'Z' && input[j] >= 'A') {
				num[input[j] - 'A']++;
			}
		}
	}
	int maxNum = *max_element(num, num + 26);
	vector<string> output(maxNum, "");
	for(int i = 0; i < maxNum; i++) {
		for(int j = 0; j < 26; j++) {
			if(num[j] > i) {
				while(output[i].size() + 1 < 2 * j) output[i] += " ";
				output[i] += (j > 0) ? " *" : "*";
			}
		}
	}
	for(int i = maxNum - 1; i >= 0; i--) {
		cout << output[i] << endl;
	}
	for(int i = 0; i < 25; i++) {
		cout << (char)('A' + i) << " ";
	}
	cout << 'Z' << endl;
	return 0;
}
