#include <cstdio>
#include <cmath>
#include <ctime>
#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
using namespace std;

const int MAX = 1001;
const int NUM = 1000;

struct Circle {
	int x, y, r;
	int o;
};

struct CircleCompare {
	bool operator() (const Circle& a, const Circle& b) {
		return a.o < b.o;
	}
};

struct CircleCompare1 {
	bool operator() (const Circle& a, const Circle& b) {
		return a.r > b.r;
	}
};

int N, W, L;
int used[MAX];
Circle cc[MAX];

bool success(int n) {
	for(int i = 0; i < N; i++) {
		if(used[cc[i].o] == 1) {
			if(pow(cc[n].x - cc[i].x, 2.0) + pow(cc[n].y - cc[i].y, 2.0) < pow(cc[n].r + cc[i].r, 2.0)) {
				return false;
			}
		}
	}
	return true;
}

int main() {
	ifstream in("in.txt");
	ofstream out("out.txt");

	int T;
	in >> T;
	for(int i = 1; i <= T; i++) {
		in >> N >> W >> L;
		if(L < W) {
			int temp = L;
			L = W;
			W = L;
		}
		for(int j = 0; j < N; j++) {
			in >> cc[j].r;
			cc[j].o = j;
			used[j] = 0;
		}

		if(N <= 4) {
			sort(cc, cc + N, CircleCompare1());
			cc[0].x = 0; cc[0].y = 0;
			cc[1].x = W; cc[1].y = L;
			cc[2].x = 0; cc[2].y = L;
			cc[3].x = W; cc[3].y = 0;
			sort(cc, cc + N, CircleCompare());
			out << "Case #" << i << ": ";
			for(int j = 0; j < N-1; j++) {
				out << cc[j].x << " " << cc[j].y << " ";
			}
			out << cc[N-1].x << " " << cc[N-1].y << endl;
			continue;
		}

		while(1) {
			for(int j = 0; j < N; j++) {
				used[j] = 0;
			}
			sort(cc, cc + N, CircleCompare1());
			cc[0].x = 0; cc[0].y = 0;
			cc[1].x = W; cc[1].y = L;
			cc[2].x = 0; cc[2].y = L;
			cc[3].x = W; cc[3].y = 0;
			used[cc[0].o] = used[cc[1].o] = used[cc[2].o] = used[cc[3].o] = 1;
			random_shuffle(cc, cc + N);

			int flag;
			for(int j = 0; j < N; j++) {
				if(used[cc[j].o] == 1) {
					continue;
				}
				flag = -1;
				for(int k = 0; k < NUM; k++) {
					srand(time(NULL));
					cc[j].x = (rand() * RAND_MAX + rand()) % W;
					cc[j].y = (rand() * RAND_MAX + rand()) % L;
					if(success(j)) {
						used[j] = 1;
						flag = 1;
						break;
					}
				}
				if(flag == -1) {
					break;
				}
			}
			if(flag == 1) {
				break;
			}
		}
		sort(cc, cc + N, CircleCompare());
		out << "Case #" << i << ": ";
		for(int j = 0; j < N-1; j++) {
			out << cc[j].x << " " << cc[j].y << " ";
		}
		out << cc[N-1].x << " " << cc[N-1].y << endl;
	}
	return 0;
}