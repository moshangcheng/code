//可以部分接受每份订票
#include <iostream>
using namespace std;

struct Order {
	int start;
	int dest;
	int num;
};

Order a[22];
int Income[8];
int Cpt, NmCityB, NmOdrs;

inline void swap(int& a, int &b) {
	int c = a;
	a = b;
	b = c;
}

void sort(Order* a) {
	for (int i = 0; i < NmOdrs; i++) {
		for (int j = i + 1; j < NmOdrs; j++) {
			if (a[i].dest > a[j].dest || (a[i].dest == a[j].dest && a[i].start
					> a[j].start)) {
				swap(a[i].start, a[j].start);
				swap(a[i].dest, a[j].dest);
				swap(a[i].num, a[j].num);
			}
		}
	}
}

int compute(Order* a) {
	int i, j = 0;
	Income[0] = 0;
	for (i = 1; i <= NmCityB; i++) {
		while (a[j].num < 1 && j < NmOdrs)
			j++;
		while (i < a[j].dest) {
			Income[i] = Income[i - 1];
			i++;
		}
		Income[i] = Income[i - 1];
		while (i == a[j].dest) {
			int D = Income[a[j].start] + i - a[j].start;
			if (Income[i] < D) {
				Income[i] = D;
				a[j].num--;
			}
			j++;
			while (a[j].num < 1 && j < NmOdrs)
				j++;
		}
	}
	return Income[NmCityB];
}

int main() {
	cin >> Cpt >> NmCityB >> NmOdrs;
	while (Cpt != 0 && NmCityB != 0 && NmOdrs != 0) {
		int sum = 0, profit;
		for (int i = 0; i < NmOdrs; i++)
			cin >> a[i].start >> a[i].dest >> a[i].num;
		sort(a);
		for (int i = 0; i < Cpt; i++) {
			profit = compute(a);
			if (profit == 0)
				break;
			else
				sum += profit;
		}
		cout << sum << endl;
		cin >> Cpt >> NmCityB >> NmOdrs;
	}
	return 0;
}

