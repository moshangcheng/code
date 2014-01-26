#include <cstdio>
#include <iostream>
#include <vector>
#include <list>
#include <fstream>
#include <algorithm>
using namespace std;

struct Node {
	int v1;
	int v2;
	int l;
	int s;
	Node(int a, int b, int c, int d): v1(a), v2(b), l(c), s(d) {}
};

struct LevelCompare {
	bool operator () (const Node& a, const Node& b) const {
		return a.v2 < b.v2;
	}
};

int main() {
	ifstream in("C:\\Users\\shu\\Desktop\\in.txt");
	ofstream out("C:\\Users\\shu\\Desktop\\out.txt");

	int T;
	in >> T;
	for(int i = 1; i <= T; i++) {
		int N;
		in >> N;
		vector<Node> level;
		for(int j = 0; j < N; j++) {
			int v1, v2;
			in >> v1 >> v2;
			level.push_back(Node(v1, v2, j, 0));
		}
		sort(level.begin(), level.end(), LevelCompare());

		bool flag = true;
		int sum = 0, starSum = 0;
		for(int j = 0; j < N; j++) {
			while(starSum < level[j].v2) {
				int num = 0;
				for(int k = N-1; k >= 0 && (level[k].s != 2); k--) {
					if(level[k].s == 0 && starSum >= level[k].v1) {
						sum++;
						num++;
						starSum += 1;
						level[k].s = 1;
						break;
					}
				}
				if(num == 0) {
					break;
				}
			}
			if(starSum < level[j].v2) {
				flag = false;
				break;
			}
			sum++;
			if(level[j].s == 1) {
				starSum += 1;
			} else if(level[j].s == 0) {
				starSum += 2;
			}
			level[j].s = 2;			
		}
		if(flag) {
			out << "Case #" << i << ": " << sum << endl;
		} else {
			out << "Case #" << i << ": " << "Too Bad" << endl;
		}
	}
	return 0;
}