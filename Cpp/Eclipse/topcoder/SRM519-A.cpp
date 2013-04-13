#include <vector>
#include <list>
#include <map>
#include <set>
#include <queue>
#include <deque>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;

string week[7] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};

class WhichDay {
public:
	string getDay(vector <string> notOnThisDay) {
		vector<int> notToday(7, 0);
		for(int i = 0; i < notOnThisDay.size(); i++) {
			for(int j = 0; j < 7; j++) {
				if(notOnThisDay[i].compare(week[j]) == 0) {
					notToday[j] = 1;
					break;
				}
			}
		}
		for(int i = 0; i < 7; i++) {
			if(notToday[i] == 0) {
				return week[i];
			}
		}

	}
};

