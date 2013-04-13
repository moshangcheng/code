/**
 * @author moshangcheng
 * @version 1.0
 * @date 2011-3-28 下午03:35:48
 * @brief http://acm.nankai.edu.cn/p1114.html
 */

#include <iostream>
#include <string>
using namespace std;

int Cord[26], flag[26], Length;
string Preorder, Inorder;

void F(int i) {
	int k = Cord[int(Preorder[i]) - 65];
	if (k > 0 && flag[int(Inorder[k - 1]) - 65] == 0) {
		int t = 1;
		flag[int(Preorder[i]) - 65] = 1;
		while (flag[int(Preorder[i + t]) - 65] != 0)
			t++;
		F(i + t);
	}
	if (k < (Length - 1) && flag[int(Inorder[k + 1]) - 65] == 0) {
		int t = 1;
		flag[int(Preorder[i]) - 65] = 1;
		while (flag[int(Preorder[i + t]) - 65] != 0)
			t++;
		F(i + t);
	}
	if (flag[int(Preorder[i]) - 65] != -1)
		cout << Preorder[i];
	flag[int(Preorder[i]) - 65] = -1;
}

int main() {
	while (cin >> Preorder >> Inorder) {
		for (int i = 0; i < 26; i++)
			flag[i] = 0;
		for (Length = 0; Inorder[Length] != '\0'; Length++)
			Cord[int(Inorder[Length]) - 65] = Length;
		F(0);
		cout << endl;
	}
	return 0;
}

