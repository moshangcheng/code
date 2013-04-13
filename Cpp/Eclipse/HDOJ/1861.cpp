/**
 * @author moshangcheng
 * @version 1.0
 * @date 2011-3-25 下午06:49:28
 * @brief http://acm.hdu.edu.cn/showproblem.php?pid=1861
 */
#include <iostream>
using namespace std;

const int MAX = 101;
struct BOAT {
	bool status;
	int hour;
	int minute;
} boat[MAX];

int main() {
	int i;
	char c1, c2;
	int number, hour, minute, time, n;
	while (1) {
		cin >> number;
		if (number == -1)
			break;
		for (i = 0; i < MAX; i++)
			boat[i].status = 1;
		for (n = time = 0; cin >> c1 >> hour >> c2 >> minute; cin >> number) {
			if (number == 0)
				break;
			if (c1 == 'S') {
				boat[number].status = 0;
				boat[number].hour = hour;
				boat[number].minute = minute;
			} else if (c1 == 'E' && boat[number].status == 0) {
				boat[number].status = 1;
				time += (hour - boat[number].hour) * 60 + (minute
						- boat[number].minute);
				n++;
			}
		}
		if (n > 0)
			cout << n << ' ' << time / n + (time % n * 2 < n ? 0 : 1) << endl;
		else
			cout << 0 << ' ' << 0 << endl;
	}
	return 0;
}
