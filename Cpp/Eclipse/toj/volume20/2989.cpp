#include <iostream>
using namespace std;

const int MAX = 1<<16;
bool state[MAX];

int op[8] = {0x0fff, 0xf0ff, 0xff0f, 0xfff0, 
			 0x7777, 0xbbbb, 0xdddd, 0xeeee};
int main()
{
	int i, j, vlu, ntest;
	state[0] = 0;
	for(i = 1; i < MAX; i++) {
		for(j = 0; j < 8; j++) {
			vlu = op[j]&i;
			if(vlu != i && !state[vlu]) break;
		}
		if(j == 8)	state[i] = 0;
		else 	 	state[i] = 1;
	}
	cin >> ntest;
	while(ntest-- > 0) {
		vlu = 0;
		for(i = 0; i < 16; i++) {
			cin >> j;
			vlu = vlu*2 + j;
		}
		if(state[vlu])  cout << "yes\n";
		else 			cout << "no\n";
	}
	return 0;
}			
