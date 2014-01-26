#include <iostream>
using namespace std;

const int INF = 1000000000;

int stack[1000], top;

inline void push(int vlu)
{
	stack[++top] = vlu;
}

inline bool empty()
{
	return top == -1;
}

inline int pop()
{
	if(empty()) {
		cout << "underflow";
		return	INF;
	}
	else return stack[top--];
}


int main()
{
	int i, j, flag, nb, n;
	while(cin >> n && n > 0)  {
		while(cin >> nb) {
			if(nb == 0) break;
			flag = 1;
			top = -1;
			for(j = 1; j < nb; j++)
				push(j);
			for(i = 1; i < n; i++)	{
				cin >> nb;
				if(!flag)	continue;
				if(nb > stack[top])
					for(j++; j < nb; j++)
						push(j);
				else if(nb == stack[top])
					pop();
				else if(nb < stack[top])
					flag = 0;
			}
			if(flag)	cout << "Yes\n";
			else		cout << "No\n";
		}
		cout << endl;
	}
	return 0;
}
