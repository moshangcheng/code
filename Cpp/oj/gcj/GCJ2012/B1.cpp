#include <cstdio>
#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
using namespace std;

int N, sum;
int v[1000];

double getMaxMin(int m, double p) {
	int tempV[1000];
	for(int i = 0, j = 0; i < N; i++, j++) {
		if(i == m) i++;
		tempV[j] = v[i];
	}
	sort(tempV, tempV + N - 1);
	double prevMax = tempV[0] + sum * p;
	for(int i = 1; i < N-1; i++) {
		if(prevMax > tempV[i]) {
			prevMax = (prevMax * i + tempV[i]) / (i + 1);
		} else {
			break;
		}
	}
	return prevMax;
}

double getAns(int m) {
	double p, beginP = 0, endP = 1.0;
	while(endP - beginP > 1e-9) {
		p = (beginP + endP) / 2.0;
		double maxMin = getMaxMin(m, p);
		if(maxMin > v[m] + sum * (1 - p)) {
			endP = p;
		} else {
			beginP = p;
		}
	}
	return (1 - p);
}

int main() {
	ifstream in("in.txt");
	ofstream out("out.txt");

	int T;
	in >> T;
	for(int i = 1; i <= T; i++) {
		sum = 0;
		in >> N;
		for(int j = 0; j < N; j++) {
			in >> v[j];
			sum += v[j];
		}
		out.setf(ios::fixed);
		out.precision(6);
		out << "Case #" << i << ":";		
		for(int j = 0; j < N; j++) {
			out << " " << 100 * getAns(j);
		}
		out << endl;
	}
	return 0;
}