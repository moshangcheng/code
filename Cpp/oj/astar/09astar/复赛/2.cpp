#include <iostream>
#include <cmath>
#include <string>
using namespace std;

struct POINT{
	int x;
	int y;
	int child;
}staff[101];

int  len[101];
int number[101];


inline int dist(const POINT& p1, const POINT& p2)	{
	return abs(p1.x-p2.x)+abs(p1.y-p2.y);
}

inline void Plus(int x, int y, string& s)	{
	s += '(';
	s += char(x+48);
	s += ',';
	s += char(y+48);
	s += ')';
}

void inc(const POINT& p1, const POINT& p2, string& s)	{
	if(p1.x < p2.x)
		for(int i = p1.x+1; i <= p2.x; i++)	Plus(i, p1.y, s); 
	else
		for(int i = p1.x-1; i >= p2.x; i--)	Plus(i, p1.y, s);
	if(p1.y < p2.y)	{
		if(p1.x != p2.x)
			for(int i = p1.y+1; i <= p2.y; i++)	Plus(p2.x, i, s);
		else
			for(int i = p1.y+1; i <= p2.y; i++)	Plus(p2.x, i, s);
	}
	else	{
		if(p1.x != p2.x)	
			for(int i = p1.y-1; i >= p2.y; i--)	Plus(p2.x, i, s);
		else
			for(int i = p1.y-1; i >= p2.y; i--)	Plus(p2.x, i, s);
	}
}

int main()
{
	int i, j;
	int N;
	
	cin >> N;
	for(i = 1; i <= N; i++)
		cin >> staff[i].x >> staff[i].y;
	cin >> staff[0].x >> staff[0].y;
	
	int Sum = 0, Num = 0;;
	for(i = 0; i <= N; i++)	{
		number[i] = 1;
		len[i] = dist(staff[i], staff[0]);
		Sum += len[i];
		staff[i].child = 0;
	}
	
	Num = N;
	int delta;
	while(1)	{
		delta = 0;
		for(i = 1; i <= N; i++)	{
			if(number[i] > 3 || number[i] == 0)	continue;
			int end1, end2;
			int d0, d1, d2, d3;
			d0 = dist(staff[0], staff[i]);
			for(j = i+1; j <= N; j++)	{
				if(number[j] + number[i] > 4 || number[j] == 0)	continue;	
				for(end1 = i; staff[end1].child > 0; end1 = staff[end1].child);				
				for(end2 = j; staff[end2].child > 0; end2 = staff[end2].child);
				d1 = dist(staff[0], staff[j]);
				d3 = dist(staff[j], staff[end1]);
				d2 = dist(staff[i], staff[end2]);
				if(d0 > d2 && d0 - d2 >= d1 - d3)	{
					number[j] += number[i];
					number[i] = 0;
					delta += d0 - d2;
					len[j] += d2 + len[i] - d0;
					staff[end2].child = i;
					Num--;	
					break;				
				}
				if(d1 > d3 && d1 - d3 > d0 - d2)	{
					number[i] += number[j];
					number[j] = 0;
					delta += d1-d3;
					len[i] += d3 + len[j] - d1;
					staff[end1].child = j;
					Num--;
				}
			}		
		}
		Sum -= delta;
		if(delta == 0)	break;
	}
	
	string route;
	cout << Sum << endl << Num << endl;
	for(i = 1; i <= N; i++)	{
		if(number[i] == 0)	continue;
		route.clear();
		cout << len[i] << ' ';
		Plus(staff[0].x, staff[0].y, route);
		int prev, cnt;
		for(prev = 0, cnt = i; cnt > 0; prev = cnt, cnt = staff[cnt].child)	{
			cout << '(' << staff[cnt].x << ',' << staff[cnt].y << ')';
			inc(staff[prev], staff[cnt], route);
		}
		cout << ':' << route << endl;
	}
	system("pause");
	return 0;
}
		
		
	
