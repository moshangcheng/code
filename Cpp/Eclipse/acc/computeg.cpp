#include <iostream>
#include <cmath>
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


//r=dotmultiply(v1, v2),
//得到矢量 v1 和 v2 的点积，如果两个矢量都非零矢量 
//r<0:两矢量夹角为锐角；r=0：两矢量夹角为直角；r>0:两矢量夹角为钝角 
double dotmultiply(const VECTOR& v1, const VECTOR& v2) 
{ 
   	double s = 0;
   	s += (v1.e.x - v1.s.x)*(v2.e.x - v2.s.x);
   	s += (v1.e.y - v1.s.y)*(v2.e.y - v2.s.y);
   	return s; 
} 
	
// 返回两个矢量 v1 和 v2 的夹角的余弦(-1 --- 1)
//注意：如果想从余弦求夹角的话，注意反余弦函数的定义域是从 0到pi 
double cosine(const VECTOR& v1, const VECTOR& v2) 
{ 
   	return dotmultiply(v1, v2)/(dist(v1.e,v1.s) * dist(v2.e,v2.s)); 
} 

double sinine(const VECTOR& v1, const VECTOR& v2)
{
	return    multiply(v1, v2)/(dist(v1.e,v1.s) * dist(v2.e,v2.s));
}

//角度小于pi，返回正值 
//角度大于pi，返回负值 
//可以用于求线段之间的夹角 (单位：弧度)
double angle(const VECTOR& v1, const VECTOR& v2) 
{ 
   double phi = acos(cosine(v1, v2));   
   if (sinine(v1, v2) < 0) return -phi;
   return phi; 
} 

// 返回点p以点o为圆心逆时针旋转alpha(单位：弧度)后所在的位置 
POINT rotate_p(const POINT& p, const POINT& o, double alpha) 
{ 
   POINT tmp; 
   tmp.x = p.x - o.x; 
   tmp.y = p.y - o.y; 
   tmp.x = tmp.x*cos(alpha) - tmp.y*sin(alpha) + o.x; 
   tmp.y = tmp.y*cos(alpha) + tmp.x*sin(alpha) + o.y; 
   return tmp; 
} 

VECTOR rotate_v(const VECTOR& v, const POINT& o, double alpha)
{
	VECTOR tmp;
	tmp.s = rotate_p(v.s, o, alpha);
	tmp.e = rotate_p(v.e, o, alpha);
	return tmp;
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

//回直线的斜率k,水平线返回 0,竖直线返回 1e200 
double slope(const LINE& l) 
{ 
   if(fabs(l.a) < 1e-20)   return 0; 
   if(fabs(l.b) < 1e-20)   return INF; 
   return -(l.a/l.b); 
} 

// 返回直线的倾斜角alpha ( 0 - pi) 
double alpha(const LINE& l) 
{ 
   if(fabs(l.a) < EP)   return 0; 
   if(fabs(l.b) < EP)   return PI/2; 
   double k = slope(l); 
   if(k > 0)  return atan(k); 
   else  return PI + atan(k); 
} 

/*****************************\ 
* * 
* 线段及直线的基本运算 * 
* * 
\*****************************/ 

/* 判断点与线段的关系,用途很广泛 
本函数是根据下面的公式写的，P是点C到线段AB所在直线的垂足 

AC dot AB 
r = --------- 
||AB||^2 
(Cx-Ax)(Bx-Ax) + (Cy-Ay)(By-Ay) 
= ------------------------------- 
L^2 

r has the following meaning: 

r=0 P = A 
r=1 P = B 
r<0 P is on the backward extension of AB 
r>1 P is on the forward extension of AB 
0<r<1 P is interior to AB 
*/ 
double relation_p_v(const POINT& p, const VECTOR& v) 
{ 
   VECTOR tmp(v.s, p); 
   return dotmultiply(tmp, v) / dotmultiply(v, v); 
} 

// 判断点p是否在线段l上，
//条件：(p在线段l所在的直线上)&& (点p在以线段l为对角线的矩形内)
bool onvector(const POINT& p, const VECTOR& v) 
{
	VECTOR v1(v.s, p), v2(v.e, p);
   	if(fabs(multiply(v1, v2)) > EP )			return 0;
   	if((v1.e.x-v1.s.x)*(v2.e.x-v2.s.x) > EP )	return 0;
	if((v1.e.y-v1.s.y)*(v2.e.y-v2.s.y) > EP) 	return 0;
   	return 1;
}
 
// 求点C到线段AB所在直线的垂足 P 
POINT perpendicular(const POINT& p, const VECTOR& v) 
{ 
   POINT tmp;
   double r = relation_p_v(p, v); 
   tmp.x = v.s.x + r*(v.e.x - v.s.x); 
   tmp.y = v.s.y + r*(v.e.y - v.s.y); 
   return tmp; 
} 

// 求点p到线段l的最短距离,并返回线段上距该点最近的点np 
//注意：np是线段l上到点p最近的点，不一定是垂足
POINT dist_p_v(const POINT& p, const VECTOR& v) 
{ 
	POINT np;
   	double r = relation_p_v(p, v); 
   	if(r < 0) { 
      	np = v.s; 
      	return dist(p, v.s); 
   	} 
   	if(r > 1) { 
      	np = v.e; 
      	return dist(p, v.e); 
   	} 
   	np = perpendicular(p, v); 
   	return  np; 
} 

// 求点p到线段l所在直线的距离,请注意本函数与上个函数的区别 
double dist_p_l(const POINT& p, const VECTOR& v) 
{
	VECTOR tmp(v.s, p);
   	return fabs(multiply(tmp, v)) / dist(v.s, v.e);
} 

//计算点到折线集的最近距离,并返回最近点. 
//注意：调用的是dist_p_v()函数 
POINT dist_p_pset(int nv, const POINT* pset, const POINT& p) 
{ 
   	VECTOR tmp; 
   	POINT minp, cntp;
   	double mind = INF, cntd;

   	for(int i = 1; i < nv; i++) { 
      	tmp.s = pset[i-1]; 
      	tmp.e = pset[ i ]; 
      	cntp = dist_p_v(p, tmp);
      	cntd = dist(cntp, p);
      	if(cntd < mind) { 
         	mind = cntd; 
         	minp = cntp; 
      	} 
   	} 
   	return minp; 
} 

//判断圆是否在多边形内. dist_ptopset()函数的应用2
bool CirInPlgn(const POINT& o, double r, int nv, const POINT* plgn) 
{ 
   double d; 
   d = dist(o, dist_p_pset(nv, plgn, o));
   if(d < r || fabs(d-r) < EP) return 1;  
   return 0; 
} 

// 求点p关于直线l的对称点 
POINT symmetry(const LINE& l, const POINT& p) 
{ 
   POINT tmp; 
   tmp.x  = ((l.b*l.b-l.a*l.a)*p.x-2*l.a*l.b*p.y-2*l.a*l.c);
   tmp.x /= (l.a*l.a+l.b*l.b); 
   tmp.y  = ((l.a*l.a-l.b*l.b)*p.y-2*l.a*l.b*p.x-2*l.b*l.c);
   tmp.y /= (l.a*l.a+l.b*l.b); 
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

//判断线段 u 是否与直线 l 相交 
//重合 0， 相交 1， 不相交 -1 
int relation_v_l(const VECTOR& u, const LINE& l, POINT& p) 
{
	LINE tmp = makeline(u.s, u.e);
	double r = relation_l_l(tmp, l, p);
	if(r == 0) 			    return  0;
	else if(r == 1) {
		if(onvector(p,u)) 	return  1;
		else 				return -1;
	}
	else if(r == -1)        return -1; 
} 

//线段和线段的关系:  不相交不共线 -2， 不相交但共线 -1
//相交但不共线 2， 相交且共线 1， 重合 0
int relation_v_v(const VECTOR& v1, const VECTOR& v2, POINT &p) 
{
	LINE l1 = makeline(v1.s, v1.e);
   	LINE l2 = makeline(v2.s, v2.e);
   	int r = relation_l_l(l1, l2, p);
	if(dist(v1.s,v2.s)<EP && dist(v1.e,v2.e)<EP)    return 0;
	if(r == -1) 									return 2;
	else if(r == 0) {
		if(onvector(v1.s,v2) || onvector(v1.e,v2))  return 1;
		else 										return 2;
	}
	else if(r == 1) {
		if(onvector(p,v1) && onvector(p,v2))		return -1;
		else 										return -2;
	}				
}

int main()
{
	POINT  p1, p2, p3;
	VECTOR v1, v2, v3;
	LINE   l1, l2, l3;
	while(1) {
		cout << "Please input two points\n";
		cin >> p1.x >> p1.y >> p2.x >> p2.y;
		
		cout << "The distance between p1 and p2 is: ";
		cout << dist(p1,p2) << endl;
		
		l1 = makeline(p1, p2);
		cout << "l1 made by p1 and p2 is: ";
		cout << "(" << l1.a << ")*x + (" << l1.b << ")*y + ";
		cout << l1.c << " = 0\n";
		cout << "The slope of l1 is " << slope(l1) << endl;
		cout << "The angle of l1 is " << alpha(l1) << endl;
		
		v1.s = p1;	v1.e = p2;
		cout << "v1 made by p1 and p2 is: ";
		cout << "(" << v1.s.x << ", " << v1.s.y << ")  ";
		cout << "(" << v1.e.x << ", " << v1.e.y << ")  \n";
		
		cout << "Please input two vectors\n";
		
	}
	return 0;
}
		
	
