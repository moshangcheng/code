#include <iostream>
#include <fstream>
using namespace std;

int main() {
	ifstream in("C:\\Documents and Settings\\moshangcheng\\桌面\\in.txt");
	int C, B, i, j;
	int calory[35001];
	int bucket[21];
	bool flag[35001][21];
	while (in >> C >> B) {
		for (i = 0; i <= C; i++)
			calory[i] = 0;
		for (i = 0; i < B; i++)
			in >> bucket[i];
		memset(flag, 0, 1);
		for (i = 1; i <= C; i++) {
			int max = 0, temp = 0, x = -1;
			for (j = 0; j < B; j++) {
				if (i >= bucket[j] && flag[i - bucket[j]][j] == 0) {
					temp = calory[i - bucket[j]] + bucket[j];
					if (temp > max) {
						max = temp;
						x = j;
					}
				}
			}
			if (x > -1) {
				calory[i] = max;
				for (j = 0; j < B; j++)
					flag[i][j] = flag[i - bucket[x]][j];
				flag[i][x] = 1;
			}
		}
		cout << calory[C] << endl;
	}
	system("pause");
	return 0;
}

