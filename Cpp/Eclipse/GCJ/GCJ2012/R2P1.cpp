#include <cstdio>
#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
using namespace std;

const int MAX = 10001;

struct Vine {
	int p, l;
};

struct VineCompare {
	bool operator() (const Vine& a, const Vine& b) {
		return a.p < b.p;
	}
};

int N, D;
int reach[MAX];
int unreach[MAX];
Vine vines[MAX];

bool search(int n, int m) {
	if(n == N || unreach[n] >= m) {
		return false;
	}
	if(reach[n] < m) {
		return true;
	}
	for(int i = n+1; i < N; i++) {
		if(vines[i].p - vines[n].p <= m) {
			if(search(i, max(vines[i].p - vines[n].p, vines[i].l))) {
				return true;
			}
		} else {
			break;
		}
	}
	return false;
}

int main() {
	ifstream in("in.txt");
	ofstream out("out.txt");

	int T;
	in >> T;
	for(int i = 1; i <= T; i++) {
		in >> N;
		for(int j = 0; j < N; j++) {
			reach[j] = 1234567890;
			unreach[j] = -1;
		}
		for(int j = 0; j < N; j++) {
			in >> vines[j].p >> vines[j].l;
		}
		in >> D;
		sort(vines, vines + N, VineCompare());
		out << "Case #" << i << ": " << (search(0, vines[0].l) ? "YES" : "NO");
		out << endl;
	}
	return 0;
}