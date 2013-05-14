#include <cstdio>
#include <string>
using namespace std;

int M, N;
const int MAX = 100;
int intLawn[MAX][MAX];
bool boolLawn[MAX][MAX];
bool flag[MAX][MAX];

bool IsPossibleBasic(bool lawn[MAX][MAX]) {
	memset(flag, 0, sizeof(flag));
	for(int i = 0; i < M; i++) {
		int plus_sum = 0;
		for(int j = 0; j < N; j++) {
			plus_sum += lawn[i][j];
		}
		if(plus_sum == 0) {
			for(int j = 0; j < N; j++) {
				flag[i][j] = 1;
			}
		}
	}
	for(int i = 0; i < N; i++) {
		int plus_sum = 0;
		for(int j = 0; j < M; j++) {
			plus_sum += lawn[j][i];
		}
		if(plus_sum == 0) {
			for(int j = 0; j < M; j++) {
				flag[j][i] = 1;
			}
		}
	}
	for(int i = 0; i < M; i++) {
		for(int j = 0; j < N; j++) {
			if(!(flag[i][j] | lawn[i][j])) {
				return false;
			}
		}
	}
	return true;
}

bool IsPossible() {
	memset(boolLawn, 0, sizeof(boolLawn));

	bool isAllTrue = true;
	for(int i = 100; i > 1; i--) {
		for(int j = 0; j < M; j++)
		for(int k = 0; k < N; k++) {
			isAllTrue &= intLawn[j][k] >= i;
			boolLawn[j][k] = (intLawn[j][k] >= i);
		}
		if(isAllTrue) {
			return true;
		}
		if(!IsPossibleBasic(boolLawn)) {
			return false;
		}
	}
	return true;
}

int main() {
	int T = 0;
	scanf("%d", &T);
	for(int i = 0; i < T; i++) {
		scanf("%d%d", &M, &N);
		for(int j = 0; j < M; j++)
		for(int k = 0; k < N; k++) {
			scanf("%d", intLawn[j] + k);
		}
		bool flag = IsPossible();

		printf("Case #%d: ", i+1);
		if(flag) {
			printf("YES\n");
		} else {
			printf("NO\n");
		}
	}
	return 0;
}