#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

/* 常用的常量定义 */ 
const double INF = 1E200;
const double EP = 1E-5; 
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

double multiply(const VECTOR& v1, const VECTOR& v2) 
{ 
   double s = 0;
   s += (v1.e.x - v1.s.x)*(v2.e.y - v2.s.y);
   s -= (v2.e.x - v2.s.x)*(v1.e.y - v1.s.y);
   return s; 
} 

bool onvector(const POINT& p, const VECTOR& v) 
{
	VECTOR v1(v.s, p), v2(v.e, p);
   	if(fabs(multiply(v1, v2)) > EP )			return 0;
   	if((v1.e.x-v1.s.x)*(v2.e.x-v2.s.x) > EP )	return 0;
	if((v1.e.y-v1.s.y)*(v2.e.y-v2.s.y) > EP) 	return 0;
   	return 1;
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

//判断线段 v 是否与直线 l 相交 
//重合 0， 相交 1， 不相交 -1 
int relation_v_l(const VECTOR& v, const LINE& l, POINT& p) 
{
	LINE tmp = makeline(v.s, v.e);
	double r = relation_l_l(tmp, l, p);
	if(r == 0) 			    return  0;
	else if(r == 1) {
		if(onvector(p,v)) 	return  1;
		else 				return -1;
	}
	else if(r == -1)        return -1; 
} 

POINT p[20], begin, end, ans[2], tmp;

int main()
{
	double s[2];
    int v1, v2, op, np;
    while(cin >> np && np > 0) {
        for(int i = 0; i < np; i++) 
			cin >> p[i].x >> p[i].y;
        cin >> begin.x >> begin.y >> end.x >> end.y;
        LINE river = makeline(begin, end);
        op = 0;
        s[0] = s[1] = 0;
        for(int i = 1; i <= np; i++) {
			v1 = i-1;
			if(i == np) v2 = 0;
			else        v2 = i;
            VECTOR e(p[v1], p[v2]);
            if(relation_v_l(e,river,tmp)==1 && dist(p[v1],tmp)>EP) {
				ans[op] = tmp;
				s[op] += p[v1].x*tmp.y - p[v1].y*tmp.x;
				op = (op+1)&1;
                s[op] += tmp.x*p[v2].y - tmp.y*p[v2].x;
            }
            else s[op] += p[v1].x*p[v2].y - p[v1].y*p[v2].x;
        }
        s[0] += ans[0].x*ans[1].y - ans[1].x*ans[0].y;
        s[1] += ans[1].x*ans[0].y - ans[0].x*ans[1].y;
        s[0] = fabs(s[0])/2;
        s[1] = fabs(s[1])/2;
        cout.setf(ios::fixed);
        cout.precision(0);
        if(s[0] > s[1]) 
        	cout << s[0] << " " << s[1] << endl;
        else 
        	cout << s[1] << " " << s[0] << endl;
    }
    return 0;
}
