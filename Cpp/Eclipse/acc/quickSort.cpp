/**
 * @author moshangcheng
 * @version 1.0
 * @date 2011-10-17 下午02:49:00
 * @brief
 */

#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;

void quickSort(int a[], int s, int e) {
	if(s >= e - 1) {
		return;
	}
	int p = s - 1, flag = a[e - 1];
	for (int i = s; i < e - 1; i++) {
		if (a[i] <= flag) {
			p++;
			swap(a[i], a[p]);
		}
	}
	swap(a[p + 1], a[e - 1]);
	quickSort(a, s, p - 1);
	quickSort(a, p + 1, e);
}

int main() {
	int a[] = { 3, 4, 2, 2, 9, 1 };
	quickSort(a, 0, 6);
	for (int i = 0; i < 6; i++) {
		cout << a[i] << " ";
	}
	cout << endl;
	return 0;
}
