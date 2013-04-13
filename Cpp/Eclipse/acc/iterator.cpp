#include <algorithm>
#include <iostream>
#include <cmath>
#include <ctime>
#include <vector>
#include <list>
#include <set>
using namespace std;

int main()
{
	int i;
	
	vector<int> V;
	vector<int>::iterator v_cnt;
	srand(time(NULL));
	for(i = 0; i < 10; i++)	{
		V.push_back(rand());
	}
	for(v_cnt = V.begin(); v_cnt != V.end(); v_cnt++)
		cout << *v_cnt << " ";
	cout << endl;
	v_cnt = V.begin() + 5;
	cout << *v_cnt << endl;
	v_cnt--;
	cout << *v_cnt << endl;
	
	list<int>	L;
	list<int>::iterator l_cnt;
		for(i = 0; i < 10; i++)	{
		L.push_back(rand());
	}
	for(l_cnt = L.begin(); l_cnt != L.end(); l_cnt++)
		cout << *l_cnt << " ";
	cout << endl;
	l_cnt = L.begin();
	advance(l_cnt, 5);
	cout << *l_cnt << endl;
	l_cnt--;
	cout << *l_cnt << endl;
	
	set<int> S;
	set<int>::iterator s_cnt;
		for(i = 0; i < 10; i++)	{
		S.insert(rand());
	}
	for(s_cnt = S.begin(); s_cnt != S.end(); s_cnt++)
		cout << *s_cnt << " ";
	cout << endl;
	s_cnt = S.begin();
	advance(s_cnt, 5);
	cout << *s_cnt << endl;
	s_cnt--;
	cout << *s_cnt << endl;
	
	system("pause");
	return 0;
}
