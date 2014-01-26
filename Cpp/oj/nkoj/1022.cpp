/**
 * @author moshangcheng
 * @version 1.0
 * @date 2011-3-28 下午03:35:48
 * @brief http://acm.nankai.edu.cn/p1022.html
 */

#include<iostream>
#include<string>
using namespace std;

char Name[20][20];
int P, M, N, c[20][20];

int Find(char*name) {
	int i;
	for (i = 0; i < M; i++) {
		if (strcmp(Name[i], name) == 0)
			break;
	}
	if (i < M)
		return i;
	else
		return -1;
}

void input(int*Judge, int*Chairman) {
	for (int j = 0; j < M; j++) {
		for (int i = 0; i < M; i++)
			c[i][j] = -1;
		Judge[j] = Chairman[j] = -1;
	}
	char speakname[200], sentence[300], name[200], temp[3];
	char iy[] = " am chairman.";
	char in[] = " am not chairman.";
	char oy[] = " is chairman.";
	char on[] = " is not chairman.";
	char T[] = "I";
	for (int k = 0; k < M; k++)
		cin >> Name[k];
	cin.getline(temp, 3, '\n');
	for (int i = 0; i < P; i++) {
		cin.getline(speakname, 200, ':');
		cin >> name;
		cin.getline(sentence, 300);
		int x = Find(speakname);
		if (x > -1) {
			if (strcmp(sentence, iy) == 0 && strcmp(name, T) == 0)
				c[x][x] = 0;
			if (strcmp(sentence, in) == 0 && strcmp(name, T) == 0)
				c[x][x] = 1;
			if (strcmp(sentence, oy) == 0) {
				int y = Find(name);
				if (y > -1)
					c[x][y] = 0;
			}
			if (strcmp(sentence, on) == 0) {
				int y = Find(name);
				if (y > -1)
					c[x][y] = 1;
			}
		}
	}
}

void xunhuan(int*Chairman, int*Judge) {
	for (int i = 0; i < M; i++) {
		int False = 0, True = 0, flag1, flag2;
		for (int j = 0; j < M; j++) {
			if (c[i][j] == 0) {
				True++;
				flag1 = j;
			}
			if (c[i][j] == 1) {
				False++;
				flag2 = j;
			}
		}
		if (True > 1)
			Judge[i] = 1;
		else if (False > 1)
			Judge[i] = 0;
		else if (True == 1 && False == 1)
			for (int k = 0; k < M; k++)
				if (k != flag1 && k != flag2)
					Chairman[k] = 1;
	}
}

void luoji(int*Judge, int*Chairman) {
	int Tjudge[20], Tchairman[20], Tc[20][20];
	for (int j = 0; j < M; j++)
		for (int k = 0; k < M; k++)
			Tc[j][k] = c[j][k];
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < M; j++) {
			Tjudge[j] = Judge[j];
			Tchairman[j] = Chairman[j];
		}
		if (Tchairman[i] == -1) {
			int True = 0, False = 0;
			for (int i2 = 0; i2 < M; i2++)
				Tchairman[i2] = 1;
			Tchairman[i] = 0;
			for (int k1 = 0; k1 < M; k1++)
				if (Tjudge[k1] == -1)
					for (int k2 = 0; k2 < M; k2++)
						if (Tc[k1][k2] > -1) {
							Tjudge[k1] = Tc[k1][k2] ^ Tchairman[k2];
							break;
						}
			for (int j1 = 0; j1 < M; j1++) {
				if (Tjudge[j1] == 1)
					False++;
				if (Tjudge[j1] == 0)
					True++;
			}
			if (False > N || True > (M - N))
				Chairman[i] = 1;
		}
	}
}

int main() {
	int Judge[20], Chairman[20];
	while (cin >> M >> N >> P) {
		input(Judge, Chairman);
		xunhuan(Chairman, Judge);
		luoji(Judge, Chairman);
		int Flag = 0, flag;
		for (int i = 0; i < M; i++)
			if (Chairman[i] == -1) {
				Flag++;
				flag = i;
			}
		if (Flag == 0)
			cout << "no\n";
		if (Flag >= 2)
			cout << "why\n";
		if (Flag == 1)
			cout << Name[flag] << endl;
	}
	return 0;
}
