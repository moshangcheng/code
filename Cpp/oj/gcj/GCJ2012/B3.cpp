#include <cstdio>
#include <iostream>
#include <vector>
#include <fstream>
#include <map>
#include <algorithm>
using namespace std;


long long N, sum;
long long v[500];
map< long long, long long> vCount;
map<long long, long long>::iterator cnt;

int main() {
	ifstream in("in.txt");
	ofstream out("out.txt");

	long long T;
	in >> T;
	for(long long i = 1; i <= T; i++) {
		in >> N;
		sum = 0;
		vCount.clear();
		for(long long j = 0; j < N; j++) {
			in >> v[j];
			sum += v[j];
		}
		sort(v, v + N);
		vCount[0] = 0;
		bool flag = false;
		for(long long j = 0; j < N; j++) {
			map<long long, long long> tempCount = vCount;
			for(cnt = vCount.begin(); cnt != vCount.end(); cnt++) {
				if(tempCount.count(cnt->first + v[j]) > 0) {
					flag = true;
					out << "Case #" << i << ":\n";
					long long cntV = cnt->first + v[j];
					cout << cntV << endl;
					out << cntV - vCount[cntV];
					for(cntV = vCount[cntV]; cntV > 0 && vCount.count(cntV) > 0; cntV = vCount[cntV]) {
						out << " " << cntV - vCount[cntV];
					}
					out << endl;
					cntV = cnt->first + v[j];
					out << v[j];
					for(cntV = cnt->first; cntV > 0 && vCount.count(cntV) > 0; cntV = vCount[cntV]) {
						out << " " << cntV - vCount[cntV];
					}
					out << endl;
					break;
				} else {
					tempCount[cnt->first + v[j]] = cnt->first;
				}
			}
			for(cnt = tempCount.begin(); cnt != tempCount.end(); cnt++) {
				if(tempCount.count(sum - cnt->first) > 0) {
					flag = true;
					out << "Case #" << i << ":\n";
					long long cntV = cnt->first + v[j];
					cout << cntV << endl;
					out << cntV - vCount[cntV];
					for(cntV = vCount[cntV]; cntV > 0 && vCount.count(cntV) > 0; cntV = vCount[cntV]) {
						out << " " << cntV - vCount[cntV];
					}
					out << endl;
					out<< "wait " << sum - cnt->first << endl;
					break;
				}
			}
			vCount = tempCount;
			if(flag) {
				break;
			}
		}
		if(!flag) {
			out << "Case #" << i << ": Impossible\n";
		}
	}
	return 0;
}