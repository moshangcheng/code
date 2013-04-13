#include <iostream>
#include <vector>
using namespace std;

struct DR {
	int x, y, d;
};

int main() {
	vector<DR> L;
	bool v[302][302];
	DR start, end, tp;
	int num_test, size, i, j;
	int dx[8] = { -2, -1, 1, 2, 2, 1, -1, -2 };
	int dy[8] = { 1, 2, 2, 1, -1, -2, -2, -1 };
	cin >> num_test;
	while (num_test-- > 0) {
		L.clear();
		memset(v, 0, sizeof(v));
		cin >> size >> start.x >> start.y >> end.x >> end.y;
		start.d = 0;
		v[start.x][start.y] = 1;
		L.push_back(start);
		for (i = 0; i < L.size(); i++) {
			if (L[i].x == end.x && L[i].y == end.y)
				break;
			for (j = 0; j < 8; j++) {
				tp.x = L[i].x + dx[j];
				tp.y = L[i].y + dy[j];
				if (tp.x < size && tp.x > -1 && tp.y < size && tp.y > -1
						&& v[tp.x][tp.y] == 0) {
					tp.d = L[i].d + 1;
					L.push_back(tp);
					v[tp.x][tp.y] = 1;
				}
			}
		}
		cout << L[i].d << endl;
	}
	return 0;
}

