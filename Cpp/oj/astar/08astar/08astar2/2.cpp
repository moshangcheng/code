#include <iostream>
#include <cmath>
#include <iomanip>
#include <algorithm>
using namespace std;

/* 常用的常量定义 */ 
const double INF = 1E200;
const double EP = 1E-6; 
const double PI = 2*acos(0); 

/* 基本几何结构 */ 
class POINT    {
	public:
      	double x, y; 
      	POINT(double a = 0, double b = 0) 
      	{ x = a; y = b;} 
      	POINT(const POINT& a) { x = a.x;	y = a.y; }
      	POINT& operator = (const POINT& a) { 
			x = a.x; y = a.y;
			return *this; 
		}
}; 

class VECTOR  { 
   	public:
      	POINT s, e;
		VECTOR() {} 
      	VECTOR(const POINT& a, const POINT& b) 
	  	{ s = a;  e = b; } 
      	VECTOR(const VECTOR& a) 
	  	{ s = a.s; e = a.e; }
	  	VECTOR& operator = (const VECTOR& a) {
			s = a.s;  e = a.e;
			return *this;
		}	  
}; 

// 直线的解析方程 a*x+b*y+c=0 为统一表示，约定 a >= 0 
class LINE  { 
   	public:
      	double a, b, c; 
      	LINE(double d1 = 1, double d2 = -1, double d3 = 0) 
      	{  a = d1;   b = d2;   c = d3;  } 
      	LINE(const LINE& t) { a = t.a;  b = t.b;  c = t.c; }
      	LINE& operator = (const LINE& t) {
			a = t.a;  b = t.b;  c = t.c;
			return *this;
		}
}; 

// 返回两点之间欧氏距离 
double dist(const POINT& p1, const POINT& p2) 
{ 
   double s = 0;
   s += (p1.x-p2.x)*(p1.x-p2.x) + (p1.y-p2.y)*(p1.y-p2.y);
   return  sqrt(s); 
} 

//r=multiply(v1, v2),得到 v1, v2的叉积 
//r>0:v2 在矢量 v1 的逆时针方向； 
//r=0：v1, v2 共线； 
//r<0:v2 在矢量 v1 的顺时针方向 
double multiply(const VECTOR& v1, const VECTOR& v2) 
{ 
   double s = 0;
   s += (v1.e.x - v1.s.x)*(v2.e.y - v2.s.y);
   s -= (v2.e.x - v2.s.x)*(v1.e.y - v1.s.y);
   return s; 
}

//求过这两点的直线解析方程： a*x+b*y+c = 0 (a >= 0) 
LINE makeline(const POINT& p1 , const POINT& p2) 
{ 
   int sign = 1;
   LINE tmp;  
   tmp.a = p2.y-p1.y; 
   if(tmp.a < 0)  { 
      sign = -1; 
      tmp.a = sign * tmp.a; 
   } 
   tmp.b = sign * (p1.x - p2.x); 
   tmp.c = sign * (p1.y*p2.x - p1.x*p2.y); 
   return tmp; 
}

//如果两条直线 l1(a1*x+b1*y+c1 = 0), l2(a2*x+b2*y+c2 = 0)
//相交 1，重合 0，不相交 -1, 且返回交点p 
int relation_l_l(const LINE& l1, const LINE& l2, POINT &p)
{ 
   	double d  = l1.a*l2.b - l2.a*l1.b;
	double d1 = l2.a*l1.c - l1.a*l2.c;
	double d2 = l2.c*l1.b - l1.c*l2.b; 
   	if(fabs(d) < EP) {
		if(fabs(d1) < EP) return  0;// 重合 
		else 		      return -1;// 平行 
	}
   	p.x = d2/d; 
   	p.y = d1/d; 
   	return 1; 
}

double triangle(const POINT& a, const POINT& b, const POINT& c)
{
	VECTOR AB(a, b), AC(a, c);
	return fabs(multiply(AB, AC)/2.0);
}

int main()
{
	int i, sita[5];
	POINT a[5], b[5];
	LINE l[5];
	double d, s[11];
	while(cin >> sita[0] >> sita[1] >> sita[2] >> sita[3] >> sita[4]) {
		sort(sita, sita+5);
		for(i = 0; i < 4; i++)//转换成弧度 
			s[i] = (sita[i+1] - sita[i])*PI/180;
		s[4] = (sita[0] + 360 - sita[4])*PI/180;
		for(i = 0; i < 5; i++)
			s[i] = s[i]/2.0 - sin(s[i])/2.0;//弓形的面积 
		for(i = 0; i < 5; i++) {
			a[i].x = cos(sita[i]*PI/180);
			a[i].y = sin(sita[i]*PI/180);
		}
		for(i = 0; i < 5; i++)
			l[i] = makeline(a[i], a[(i+2)%5]);
		for(i = 0; i < 5; i++)
			relation_l_l(l[i], l[(i+4)%5], b[i]);
		for(i = 0; i < 5; i++)	{
			s[i]  += triangle(a[i], b[i], a[(i+1)%5]);//得出扇形的面积 
			s[5+i] = triangle(a[i], b[i], b[(i+4)%5]);
		}
		s[10] = PI;
		for(i = 0; i < 10; i++)
			s[10] -= s[i];
		d = 0.0;
		for(i = 0; i < 11; i++)
			d += (s[i] - PI/11)*(s[i] - PI/11);
		d /= 11;
		cout.setf(ios::fixed);
		cout.precision(4);
		cout << d << endl;
	}
	return 0;
}
		
