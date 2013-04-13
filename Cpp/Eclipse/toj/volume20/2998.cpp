#include <iostream>
#include <vector>
using namespace std;

int size_d, H, W;
vector<int> L[3];
int pos[100][2];
bool vst[300][300];
char table[150][150];

int go(const pair<int, int>& d) {
	int i, s, x, y;
	s = 0;
	for (i = 0; i < size_d; i++) {
		x = d.first + pos[i][0];
		y = d.second + pos[i][1];
		if (x >= 0 && x < H && y >= 0 && y < W) {
			if (table[x][y] == 'O')
				return -1;
			else if (table[x][y] == 'Q')
				s++;
		} else
			return -1;
	}
	if (s > 0)
		return 0;
	else
		return 1;
}

int main() {
	bool yeah;
	int i, j, vlu;
	pair<int, int> tmp;
	int drc[4][2] = { -1, 0, 0, 1, 1, 0, 0, -1 };
	while (cin >> H >> W) {
		if (H == 0 && W == 0)
			break;
		size_d = 0;
		for (i = 0; i < H; i++)
			for (j = 0; j < W; j++) {
				cin >> table[i][j];
				if (table[i][j] == 'D') {
					pos[size_d][0] = i;
					pos[size_d++][1] = j;
				}
			}
		memset(vst, 0, sizeof(vst));
		vst[H][W] = 1;
		for (i = 0; i < 3; i++) {
			L[i].clear();
			L[i].push_back(0);
		}
		yeah = 0;
		for (i = 0; i < L[0].size(); i++) {
			for (j = 0; j < 4; j++) {
				tmp.first = L[0][i] + drc[j][0];
				tmp.second = L[1][i] + drc[j][1];
				if (vst[tmp.first + H][tmp.second + W])
					continue;
				vlu = go(tmp);
				if (vlu == 0) {
					yeah = 1;
					break;
				} else if (vlu == 1) {
					L[0].push_back(tmp.first);
					L[1].push_back(tmp.second);
					L[2].push_back(L[2][i] + 1);
					vst[tmp.first + H][tmp.second + W] = 1;
				}
			}
			if (yeah)
				break;
		}
		if (yeah)
			cout << L[2][i] + 1 << endl;
		else
			cout << "Impossible\n";
	}
	return 0;
}

