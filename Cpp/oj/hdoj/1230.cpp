/**
 * @author moshangcheng
 * @version 1.0
 * @date 2011-3-25 下午06:49:28
 * @brief http://acm.hdu.edu.cn/showproblem.php?pid=1230
 */
#include <iostream>
#include <string>
using namespace std;

const int MAX = 100;
bool notprime[MAX];
int pn, prime[MAX], value_a[MAX], value_b[MAX], value[MAX];

void gen_prime() {
	int i, j;
	memset(notprime, 0, sizeof(notprime));
	for (pn = 0, i = 2; i < MAX; i++) {
		if (!notprime[i])
			prime[pn++] = i;
		for (j = 0; j < pn && prime[j] * i < MAX; j++) {
			notprime[prime[j] * i] = 1;
			if (i % prime[j] == 0)
				break;
		}
	}

}

int main() {
	int i;
	char tmp_char;
	int size_a, size_b, size;
	int sum, carry;
	gen_prime();
	while (1) {
		for (size_a = 0;;) {
			cin >> value_a[size_a++];
			cin.get(tmp_char);
			if (tmp_char == ' ')
				break;
		}
		for (size_b = 0;;) {
			cin >> value_b[size_b++];
			cin.get(tmp_char);
			if (tmp_char == '\n')
				break;
		}
		if (size_a == 1 && size_b == 1 && value_a[0] == 0 && value_b[0] == 0)
			break;
		for (size = carry = i = 0;; value[size++] = sum, i++) {
			sum = carry;
			if (i < size_a) {
				sum += value_a[size_a - 1 - i];
				if (i < size_b)
					sum += value_b[size_b - 1 - i];
			} else if (i < size_b)
				sum += value_b[size_b - 1 - i];
			else if (sum == 0)
				break;
			carry = sum / prime[i];
			sum %= prime[i];
		}
		for (i = size - 1; i > 0; i--)
			cout << value[i] << ',';
		cout << value[0] << endl;
	}
	return 0;
}
