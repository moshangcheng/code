/**
 * @author moshangcheng
 * @version 1.0
 * @date 2011-8-12 下午07:57:52
 * @brief GCJ2011 R1A B
 * http://code.google.com/codejam/contest/dashboard?c=1145485#s=p1
 * http://code.google.com/codejam/contest/dashboard?c=1145485#s=a&a=1
 *
 */
#include <iostream>
#include <cstdio>
#include <cmath>
#include <vector>
#include <set>
using namespace std;

vector<string> D;
vector<string> V;
vector<int> P;
set<string> S;

int source(istream& cin, ostream& cout) {
	//int main() {
	int T;
	cin >> T;
	for (int i = 0; i < T; i++) {
		int N, M;
		cin >> N >> M;
		D.clear();
		for (int j = 0; j < N; j++) {
			string d;
			cin >> d;
			D.push_back(d);
		}
		cout << "Case #" << i + 1 << ":";
		for (int j = 0; j < M; j++) {
			string L;
			cin >> L;
			P.clear();
			V.clear();
			for (int j = 0; j < N; j++) {
				V.push_back(string(D[j].size(), '_'));
				P.push_back(0);
				for (int k = 0; k < L.size(); k++) {
					if (D[j].find(L[k], 0) != string::npos) {
						P[j]--;
					}
				}
			}
			for (int j = 0; j < L.size(); j++) {
				S.clear();
				for (int k = 0; k < N; k++) {
					if (D[k].find(L[j], 0) != string::npos) {
						S.insert(V[k]);
					}
				}
				for (int k = 0; k < N; k++) {
					if (S.find(V[k]) != S.end()) {
						P[k]++;
					}
				}
				for (int k = 0; k < N; k++) {
					for (int l = 0; l < V[k].size(); l++) {
						if (D[k][l] == L[j]) {
							V[k][l] = L[j];
						}
					}
				}
			}
			int maxIt = 0;
			for (int j = 1; j < N; j++) {
				if (P[j] > P[maxIt]) {
					maxIt = j;
				}
			}
			cout << " " << D[maxIt];
		}
		cout << endl;
	}
	return 0;
}
