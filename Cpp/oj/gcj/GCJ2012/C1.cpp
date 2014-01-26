#include <cstdio>
#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
using namespace std;

const int MAX = 1001;


vector<int> q;
vector<int> p[MAX];
int used[MAX];


int main() {
	ifstream in("in.txt");
	ofstream out("out.txt");

	int T;
	in >> T;
	for(int i = 1; i <= T; i++) {
		int N;
		in >> N;
		for(int j = 1; j <= N; j++) {
			p[j].clear();
			int tempN, tempV;
			in >> tempN;
			for(int k = 0; k < tempN; k++) {
				in >> tempV;
				p[j].push_back(tempV);
			}
		}
		bool flag = false;
		memset(used, 0, sizeof(used));
		for(int j = 1; j <= N; j++) {
			//if(used[j]) continue;
			memset(used, 0, sizeof(used));
			q.clear();
			q.push_back(j);
			for(int k = 0; k < q.size(); k++) {
				if(used[q[k]]) {
					flag = true;
					break;
				}
				used[q[k]] = true;
				for(int l = 0; l < p[q[k]].size(); l++) {
					q.push_back(p[q[k]][l]);
				}
			}
			if(flag) {
				break;
			}
		}
		out << "Case #" << i << ": " << (flag ? "Yes" : "No");
		out << endl;
	}
	return 0;
}