#include <cstdio>
#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
using namespace std;

typedef long long ll;

struct Node {
	ll type;
	ll num;
	Node() {}
	Node(ll a, ll b) : num(a), type(b) {}
};

const ll MAX = 1011;

Node A[2][MAX];
ll s[MAX][MAX];


ll N, M;

ll getMax(ll x, ll y, ll u, ll v) {
	ll maxS;
	if(x < y) {
		maxS = s[u+1][v+1] + x;
		for(u++; u < N; u++) {
			if(A[0][u].type == A[1][v].type) {
				ll tempV = x + getMax(A[0][u].num, y - x, u, v);
				if(tempV > maxS) {
					maxS = tempV;
				}
				break;
			}
		}
	} else if(x > y) {
		maxS = s[u+1][v+1] + y;
		for(v++; v < M; v++) {
			if(A[1][v].type == A[0][u].type) {
				ll tempV = y + getMax(x - y, A[1][v].num, u, v);
				if(tempV > maxS) {
					maxS = tempV;
				}
				break;
			}
		}
	} else {
		maxS = s[u+1][v+1] + y;
	}
	return maxS;
}

int main() {
	ifstream in("in.txt");
	ofstream out("out.txt");

	ll T;
	in >> T;
	for(ll i = 1; i <= T; i++) {
		in >> N >> M;
		s[N][M] = 0;
		for(ll j = 0; j < N; j++) {
			ll v1, v2;
			in >> v1 >> v2;
			A[0][j] = Node(v1, v2);
			s[j][M] = 0;
		}
		for(ll j = 0; j < M; j++) {
			ll v1, v2;
			in >> v1 >> v2;
			A[1][j] = Node(v1, v2);
			s[N][j] = 0;
		}
		for(ll j = N-1; j >= 0; j--) {
			for(ll k = M-1; k >=0; k--) {
				s[j][k] = s[j+1][k] > s[j][k+1] ? s[j+1][k] : s[j][k+1];
				if(A[0][j].type == A[1][k].type) {
					ll maxS = getMax(A[0][j].num, A[1][k].num, j, k);
					if(s[j][k] < maxS) {
						s[j][k] = maxS;
					}
				}
			}
		}
		out << "Case #" << i << ": " << s[0][0];
		out << endl;
	}
	return 0;
}