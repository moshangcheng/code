/*
 ID: aamosha1
 PROG: packrec
 LANG: C++
 */
#include <iostream>
#include <fstream>
using namespace std;

int S = 10000, num = 0;
int Max[300][2];
int height[4], width[4];

void f(int*, int*);
void Compare(int maxw, int maxh);

int main() {
	ifstream fin("packrec.in");
	ofstream fout("packrec.out");

	int i, j, temp;
	int width[4], height[4];
	int tempw[4], temph[4];
	int a[4] = { 0, 0, 0, 0 };

	for (i = 0; i < 4; i++)
		fin >> width[i] >> height[i];
	for (i = 0; i < 4; i++) {
		if (a[i]) {
			tempw[i] = height[i];
			temph[i] = width[i];
		} else {
			tempw[i] = width[i];
			temph[i] = height[i];
		}
	}
	f(tempw, temph);
	while (1) {
		for (i = 0; i < 4; i++) {
			if (a[i] == 0) {
				a[i] = 1;
				for (j = 0; j < i; j++)
					a[j] = 0;
				for (j = 0; j < 4; j++) {
					if (a[j]) {
						tempw[j] = height[j];
						temph[j] = width[j];
					} else {
						tempw[j] = width[j];
						temph[j] = height[j];
					}
				}
				f(tempw, temph);
				break;
			}
		}
		if (i == 4)
			break;
	}

	fout << S << endl;

	for (i = 0; i < num; i++)
		if (Max[i][0] > Max[i][1]) {
			temp = Max[i][0];
			Max[i][0] = Max[i][1];
			Max[i][1] = temp;
		}

	for (i = 0; i < num; i++)
		for (j = i + 1; j < num; j++)
			if (Max[i][0] > Max[j][0]) {
				temp = Max[i][0];
				Max[i][0] = Max[j][0];
				Max[j][0] = temp;
				temp = Max[i][1];
				Max[i][1] = Max[j][1];
				Max[j][1] = temp;
			}
	for (i = 0; i < num; i++)
		fout << Max[i][0] << " " << Max[i][1] << endl;
	return 0;
}

void Compare(int maxw, int maxh) {
	int i;
	if (maxw * maxh < S) {
		num = 0;
		Max[num][0] = maxw;
		Max[num][1] = maxh;
		S = maxw * maxh;
		num = 1;
	} else if (maxw * maxh == S) {
		for (i = 0; i < num; i++)
			if (maxw == Max[i][0] || maxw == Max[i][1])
				break;
		if (i == num) {
			Max[num][0] = maxw;
			Max[num][1] = maxh;
			num++;
		}
	}
}

void f(int*width, int*height) {
	int i, j, k, l, m;
	int maxw, maxh;

	for (i = 0; i < 5; i++) {
		if (i == 0) {
			maxw = maxh = 0;
			for (j = 0; j < 4; j++) {
				maxw += width[j];
				if (maxh < height[j])
					maxh = height[j];
			}
			Compare(maxw, maxh);
		}

		if (i == 1) {
			for (j = 0; j < 4; j++) {
				maxw = maxh = 0;
				for (k = 0; k < 4; k++)
					if (k != j) {
						maxw += width[k];
						if (maxh < height[k])
							maxh = height[k];
					}
				maxw = (maxw > width[j]) ? maxw : width[j];
				maxh += height[j];
				Compare(maxw, maxh);
			}
		}

		if (i == 2) {
			for (j = 0; j < 4; j++)
				for (k = 0; k < 4; k++)
					if (k != j) {
						maxw = maxh = 0;
						for (l = 0; l < 4; l++) {
							if (l != k && l != j) {
								maxw += width[l];
								if (maxh < height[l])
									maxh = height[l];
							}
						}
						maxw = (maxw > width[k]) ? maxw : width[k];
						maxh += height[k];
						maxw += width[j];
						maxh = (maxh > height[j]) ? maxh : height[j];
						Compare(maxw, maxh);
					}
		}

		if (i == 3) {
			for (j = 0; j < 4; j++)
				for (k = 0; k < 4; k++)
					if (j != k) {
						maxw = maxh = 0;
						for (l = 0; l < 4; l++)
							if (l != j && l != k) {
								if (maxw < width[l])
									maxw = width[l];
								maxh += height[l];
							}
						maxw += width[j] + width[k];
						maxh = (maxh > height[j]) ? maxh : height[j];
						maxh = (maxh > height[k]) ? maxh : height[k];
						Compare(maxw, maxh);
					}
		}

		if (i == 4) {
			for (j = 0; j < 4; j++)
				for (k = 0; k < 4; k++)
					if (j != k)
						for (l = 0; l < 4; l++)
							if (l != j && l != k)
								for (m = 0; m < 4; m++) {
									if (m == j || m == k || m == l)
										break;
									maxw = 0;
									maxh = (height[j] + height[l]) > (height[k]
											+ height[m]) ? height[j]
											+ height[l] : height[k] + height[m];
									maxw = maxw > width[l] ? maxw : width[l];
									maxw = maxw > width[m] ? maxw : width[m];
									maxw = maxw > (width[j] + width[k]) ? maxw
											: (width[j] + width[k]);
									if (height[j] < height[k])
										maxw
												= maxw > (width[k] + width[l]) ? maxw
														: (width[k] + width[l]);
									else
										maxw
												= maxw > (width[j] + width[m]) ? maxw
														: (width[j] + width[m]);
									if (height[j] + height[l] > height[k])
										maxw
												= maxw > (width[l] + width[m]) ? maxw
														: (width[l] + width[m]);
									Compare(maxw, maxh);
								}
		}
	}
}

