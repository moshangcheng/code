#include <cstdio>
#include <string>
using namespace std;

bool hasEmpty;
char v[4][4];

int check(char (&ca)[4]) {
	int o_num = 0;
	int x_num = 0;
	for(int j = 0; j < 4; j++) {
		switch(ca[j]) {
		case 'O':
			o_num++;
			break;
		case 'X':
			x_num++;
			break;
		case '.':
			hasEmpty = true;
			break;
		default:
			o_num++;
			x_num++;
			break;
		}
	}
	if(o_num == 4) {
		return 1;
	} else if(x_num == 4) {
		return -1;
	} else {
		return 0;
	}
}

int main() {
	int T = 0;
	scanf("%d", &T);
	for(int i = 0; i < T; i++) {
		hasEmpty = false;
		for(int j = 0; j < 4; j++) {
			scanf("%s", v[j]);
		}

		int flag = 0;
		for(int j = 0; j < 4; j++) {
			flag = check(v[j]);
			if(flag != 0) {
				break;
			}
		}
		for(int j = 0; flag == 0 && j < 4; j++) {
			char tmp[4];
			for(int k = 0; k < 4; k++) {
				tmp[k] = v[k][j];
			}
			flag = check(tmp);
			if(flag != 0) {
				break;
			}
		}
		for(int j = 0; flag == 0 && j < 2; j++) {
			char tmp[4];
			for(int k = 0; k < 4; k++) {
				tmp[k] = v[k][(j == 0) ? 3-k : k];
			}
			flag = check(tmp);
			if(flag != 0) {
				break;
			}
		}
		printf("Case #%d: ", i+1);
		switch(flag){
		case 1:
			printf("O won\n");
			break;
		case -1:
			printf("X won\n");
			break;
		default:
			if(hasEmpty){
				printf("Game has not completed\n");
			} else {
				printf("Draw\n");
			}
			break;
		}
	}
	return 0;
}