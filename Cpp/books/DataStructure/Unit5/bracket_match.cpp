#include <iostream>
#include <string>
#include <stdio.h>
#include "stack.h"
using namespace std;

const int MaxLength = 100;

void PrintMatcnedPairs(char*expr) {
	Stack<int> s(MaxLength);
	int j, length = strlen(expr);
	for (int i = 0; i < length; i++) {
		if (expr[i] == '(')
			s.Add(i + 1);
		else if (expr[i] == ')') {
			if (s.IsEmpty())
				cout << "No match for right parenthesis " << "at " << i + 1
						<< endl;
			else {
				s.Delete(j);
				cout << j << " " << i + 1 << endl;
			}
		}
	}
	while (!s.IsEmpty()) {
		s.Delete(j);
		cout << "No match for left parenthesis at " << j << endl;
	}
}

int main() {
	char expr[MaxLength];
	cout << "Type an expression of length at most " << MaxLength << endl;
	cin.getline(expr, MaxLength);
	cout << "The pairs of matchign parenthesis in " << endl;
	puts(expr);
	cout << "are " << endl;
	PrintMatcnedPairs(expr);
	system("pause");
	return 0;
}
