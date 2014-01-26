#include <iostream>
using namespace std;

const int MAX = 1001;
int price[MAX];
bool vst[MAX];

int main()
{
	int i, j, ndish, maxp, sum;
	while(cin >> ndish && ndish > 0) {
		for(i = 0; i < ndish; i++)  {
			cin >> price[i];
			if(i == 0)  maxp = i;
			else if(price[i] > price[maxp])  
				maxp = i;
		}
		cin >> sum;
		memset(vst, 0, sizeof(vst));
		vst[0] = 1;
		for(i = 0; i < ndish; i++)  {
			if(i == maxp)	continue;
			for(j = MAX-1; j >= 0; j--)
				if(vst[j] && (j+price[i] < MAX) )
				vst[j+price[i]] = 1;
		}
		for(i = sum-5; i > 0 && (!vst[i]); i--);
		if(i < 0)	cout << sum << endl;
		else	cout << sum - i - price[maxp] << endl;
	}
	return 0;
}
