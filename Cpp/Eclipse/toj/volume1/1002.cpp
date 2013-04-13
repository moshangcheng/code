#include <iostream>
#include <string>
#include <strstream>
using namespace std;

int main() {
	int N, date;
	int i, j, k;
	int Day, Year, period, day, year;
	char In[10];
	string Month;
	string Haab[19] = { "pop", "no", "zip", "zotz", "tzec", "xul", "yoxkin",
			"mol", "chen", "yax", "zac", "ceh", "mac", "kankin", "muan", "pax",
			"koyab", "cumhu", "uayet" };
	string Tzolkin[20] = { "imix", "ik", "akbal", "kan", "chicchan", "cimi",
			"manik", "lamat", "muluk", "ok", "chuen", "eb", "ben", "ix", "mem",
			"cib", "caban", "eznab", "canac", "ahau" };
	cin >> N;
	cout << N << endl;
	for (i = 0; i < N; i++) {
		cin.getline(In, 10, '.');
		istrstream inS(In);
		inS >> Day;
		cin >> Month >> Year;

		for (j = 0; j < 19; j++)
			if (Month == Haab[j])
				break;
		date = Year * 365 + Day + j * 20;
		year = date / 260;
		date -= year * 260;
		period = date % 13 + 1;
		day = date % 20;

		cout << period << ' ' << Tzolkin[day] << ' ' << year << endl;
	}
	return 0;
}

