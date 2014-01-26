//用来产生长度至多为MAX的序列表示的所有数 
//长度为MAX的序列，可用 MAX-2 位的 N! 进制数表示
//例如 3: 0     1->2->3
//     4: 00    1->2->3->4   1 1->2->4
//     5: 01    1->2->4->5   10 1->2->3->5  000 1->2->3->4->5
//     6: 11    1->2->4->6   20 1->2->3->6  100 1->2->3->4->6
//        001   1->2->4->5->6
//        010   1->2->3->5->6
//        0000  1->2->3->4->5->6
#include <iostream>
using namespace std;

const int MAX = 5;
const int VLU = 1 << (MAX - 1);
int a[MAX + 1], num[VLU + 1];

void gen(int m) {
	if (m > MAX)
		return;
	num[a[m]]++;
	for (int i = m; i >= 1; i--) {
		a[m + 1] = a[m] + a[i];
		gen(m + 1);
	}
}

int main() {
	memset(num, 0, sizeof(num));
	a[1] = 1;
	gen(1);

	for (int i = 1; i <= VLU; i++)
		cout << i << " " << num[i] << endl;
	system("pause");
	return 0;
}
