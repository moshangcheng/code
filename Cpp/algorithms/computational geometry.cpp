#include <cmath > 

/* 常用的常量定义 */ 
const double INF = 1E200;
const double EP = 1E-10;
const int MAXV = 300; 
const double PI = 2*acos(0); 

/* 基本几何结构 */ 
class POINT    {
   public:
      double x; 
      double y; 
      //constructor 
      POINT(double a = 0, double b = 0) 
      { x = a; y = b;} 
}; 

class LINESEG  { 
   public:
      POINT s; 
      POINT e; 
      LINESEG(POINT a, POINT b) { s = a; e = b;} 
      LINESEG() { } 
}; 

// 直线的解析方程 a*x+b*y+c=0 为统一表示，约定 a >= 0 
class LINE  { 
   public:
      double a; 
      double b; 
      double c; 
      LINE(double d1 = 1, double d2 = -1, double d3 = 0) 
      {  a = d1;   b = d2;   c = d3;  } 
}; 

/********************\ 
* * 
* 点的基本运算 * 
* * 
\********************/ 

// 返回两点之间欧氏距离 
double dist(POINT p1,POINT p2) 
{ 
   double s = 0;
   s += (p1.x - p2.x)*(p1.x - p2.x) + (p1.x - p2.x)*(p1.x - p2.x);
   return  sqrt(s); 
} 

// 判断两个点是否重合 
bool equal_point(POINT p1, POINT p2) 
{ 
  return (dist(p1, p2) < EP);
}

//r=multiply(sp,ep,op),得到(sp-op)*(ep-op)的叉积 
//r>0:ep在矢量opsp的逆时针方向； 
//r=0：opspep三点共线； 
//r<0:ep在矢量opsp的顺时针方向 
double multiply(POINT sp, POINT ep, POINT op) 
{ 
   double s = 0;
   s += (sp.x - op.x)*(ep.y - op.y) - (ep.x - op.x)*(sp.y - op.y);
   return s; 
} 


//r=dotmultiply(p1,p2,op),
//得到矢量(p1-op)和(p2-op)的点积，如果两个矢量都非零矢量 
//r<0:两矢量夹角为锐角；r=0：两矢量夹角为直角；r>0:两矢量夹角为钝角 
double dotmultiply(POINT p1, POINT p2, POINT p0) 
{ 
   double s = 0;
   s += (p1.x - p0.x)*(p2.x - p0.x) + (p1.y - p0.y)*(p2.y - p0.y)
   return s; 
} 

// 判断点p是否在线段l上，
//条件：(p在线段l所在的直线上)&& (点p在以线段l为对角线的矩形内)
bool online(LINESEG l,POINT p) 
{
   if(multiply(l.e, p, l.s) != 0) return 0;
   if(((p.x-l.s.x)*(p.x-l.e.x) <= 0) && ((p.y-l.s.y)*(p.y-l.e.y) <=0))
      return 1;
   else return 0;
} 

// 返回点p以点o为圆心逆时针旋转alpha(单位：弧度)后所在的位置 
POINT rotate(POINT o, double alpha, POINT p) 
{ 
   POINT tp; 
   p.x -= o.x; 
   p.y -= o.y; 
   tp.x = p.x*cos(alpha) - p.y*sin(alpha) + o.x; 
   tp.y = p.y*cos(alpha) + p.x*sin(alpha) + o.y; 
   return tp; 
} 

// 返回顶角在o点，起始边为os，终止边为oe的夹角(单位：弧度) 
//角度小于pi，返回正值 
//角度大于pi，返回负值 
//可以用于求线段之间的夹角 
double angle(POINT o, POINT s, POINT e) 
{ 
   double cosfi, fi, norm; 
   double dsx = s.x - o.x; 
   double dsy = s.y - o.y; 
   double dex = e.x - o.x; 
   double dey = e.y - o.y; 

   cosfi = dsx*dex + dsy*dey; 
   norm = (dsx*dsx + dey*dey)*(dex*dex + dey*dey); 
   cosfi /= sqrt(norm); 

   if (cosfi >= 1.0 ) return 0; 
   if (cosfi <= -1.0 ) return PI; 

   fi = acos(cosfi); 
   // 说明矢量os 在矢量 oe的顺时针方向 
   if (dsx*dey - dsy*dex > 0) return fi;
   return -fi; 
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
double relation(POINT p, LINESEG l) 
{ 
   double s = 0;
   LINESEG tl; 
   tl.s = l.s; 
   tl.e = p;
   s = dotmultiply(tl.e, l.e, l.s);
   return s / (dist(l.s,l.e)*dist(l.s,l.e)); 
} 

// 求点C到线段AB所在直线的垂足 P 
POINT perpendicular(POINT p, LINESEG l) 
{ 
   double r = relation(p, l); 
   POINT tp; 
   tp.x = l.s.x + r*(l.e.x - l.s.x); 
   tp.y = l.s.y + r*(l.e.y - l.s.y); 
   return tp; 
} 

// 求点p到线段l的最短距离,并返回线段上距该点最近的点np 
//注意：np是线段l上到点p最近的点，不一定是垂足
double ptolinesegdist(POINT p, LINESEG l, POINT &np) 
{ 
   double r = relation(p,l); 
   if(r < 0) { 
      np = l.s; 
      return dist(p, l.s); 
   } 
   if(r > 1) { 
      np = l.e; 
      return dist(p, l.e); 
   } 
   np = perpendicular(p,l); 
   return  dist(p,np); 
} 

// 求点p到线段l所在直线的距离,请注意本函数与上个函数的区别 
double ptoldist(POINT p, LINESEG l) 
{ 
   double d = 0;
   d = fabs(multiply(p, l.e, l.s)) / dist(l.s,l.e);
   return d; 
} 

//计算点到折线集的最近距离,并返回最近点. 
//注意：调用的是ptolineseg()函数 
double ptopointset(int vcount, POINT pointset[], POINT p, POINT &q) 
{ 
   int i; 
   double cd = double(INF), td; 
   LINESEG l; 
   POINT tq, cq; 

   for(i = 0; i < vcount-1; i++) { 
      l.s = pointset[ i ]; 
      l.e = pointset[i+1]; 
      td = ptolinesegdist(p, l, tq); 
      if(td < cd) { 
         cd = td; 
         cq = tq; 
      } 
   } 
   q = cq; 
   return cd; 
} 
//判断圆是否在多边形内.ptolineseg()函数的应用2
bool CirInPlgn(int vcount, POINT center, double radius, POINT polygon[]) 
{ 
   POINT q; 
   double d; 
   q.x = 0; 
   q.y = 0; 
   d = ptopointset(vcount, polygon, center, q); 
   if(d < radius || fabs(d-radius) < EP) 
      return 1;  
   return 0; 
} 

// 返回两个矢量l1和l2的夹角的余弦(-1 --- 1)
//注意：如果想从余弦求夹角的话，注意反余弦函数的定义域是从 0到pi 
double cosine(LINESEG l1, LINESEG l2) 
{ 
   double sum = 0;
   sum += (l1.e.x - l1.s.x) * (l2.e.x - l2.s.x);
   sum += (l1.e.y - l1.s.y) * (l2.e.y - l2.s.y);
   return sum / (dist(l1.e, l1.s) * dist(l2.e, l2.s)); 
} 

// 返回线段l1与l2之间的夹角 单位：弧度 范围(-pi，pi) 
double lsangle(LINESEG l1, LINESEG l2) 
{ 
   POINT o, s, e; 
   o.x = o.y = 0; 
   s.x = l1.e.x - l1.s.x; 
   s.y = l1.e.y - l1.s.y; 
   e.x = l2.e.x - l2.s.x; 
   e.y = l2.e.y - l2.s.y; 
   return angle(o, s, e); 
} 

// 如果线段u和v相交(包括相交在端点处)时，返回true 
bool intersect(LINESEG u, LINESEG v) 
{ 
   return( (max(u.s.x,u.e.x)>=min(v.s.x,v.e.x))&& //排斥实验 
   (max(v.s.x,v.e.x)>=min(u.s.x,u.e.x))&& 
   (max(u.s.y,u.e.y)>=min(v.s.y,v.e.y))&& 
   (max(v.s.y,v.e.y)>=min(u.s.y,u.e.y))&& 
   (multiply(v.s,u.e,u.s)*multiply(u.e,v.e,u.s)>=0)&& //跨立实验 
   (multiply(u.s,v.e,v.s)*multiply(v.e,u.e,v.s)>=0)); 
} 


// (线段u和v相交)&&(交点不是双方的端点) 时返回true 
bool intersect_A(LINESEG u, LINESEG v) 
{ 
   return((intersect(u,v))&& 
   (!online(u,v.s))&& 
   (!online(u,v.e))&& 
   (!online(v,u.e))&& 
   (!online(v,u.s))); 
} 


// 线段v所在直线与线段u相交时返回true；方法：判断线段u是否跨立线段v 
bool intersect_l(LINESEG u, LINESEG v) 
{ 
return multiply(u.s,v.e,v.s)*multiply(v.e,u.e,v.s)>=0; 
} 


// 根据已知两点坐标，求过这两点的直线解析方程： a*x+b*y+c = 0 (a >= 0) 
LINE makeline(POINT p1 , POINT p2) 
{ 
   LINE tl; 
   int sign = 1; 
   tl.a = p2.y-p1.y; 
   if(tl.a < 0)  { 
      sign = -1; 
      tl.a = sign * tl.a; 
   } 
   tl.b = sign * (p1.x - p2.x); 
   tl.c = sign * (p1.y*p2.x - p1.x*p2.y); 
   return tl; 
} 

// 根据直线解析方程返回直线的斜率k,水平线返回 0,竖直线返回 1e200 
double slope(LINE l) 
{ 
   if(fabs(l.a) < 1e-20)   return 0; 
   if(fabs(l.b) < 1e-20)   return INF; 
   return -(l.a/l.b); 
} 

// 返回直线的倾斜角alpha ( 0 - pi) 
double alpha(LINE l) 
{ 
   if(fabs(l.a) < EP)   return 0; 
   if(fabs(l.b) < EP)   return PI/2; 
   double k = slope(l); 
   if(k > 0)  return atan(k); 
   else  return PI + atan(k); 
} 

// 求点p关于直线l的对称点 
POINT symmetry(LINE l, POINT p) 
{ 
   POINT tp; 
   tp.x = ((l.b*l.b-l.a*l.a)*p.x-2*l.a*l.b*p.y-2*l.a*l.c)/(l.a*l.a+l.b*l.b); 
   tp.y = ((l.a*l.a-l.b*l.b)*p.y-2*l.a*l.b*p.x-2*l.b*l.c)/(l.a*l.a+l.b*l.b); 
   return tp; 
} 

//如果两条直线 l1(a1*x+b1*y+c1 = 0), l2(a2*x+b2*y+c2 = 0)
//相交，返回true，且返回交点p 
bool lineintersect(LINE l1,LINE l2,POINT &p) // 是 L1，L2 
{ 
   double d = l1.a*l2.b - l2.a*l1.b; 
   if(fabs(d) < EP) // 不相交 
   return false; 
   p.x = (l2.c*l1.b - l1.c*l2.b)/d; 
   p.y = (l2.a*l1.c - l1.a*l2.c)/d; 
   return true; 
} 

// 如果线段l1和l2相交，返回true且交点由(inter)返回，否则返回false 
bool intersection(LINESEG l1, LINESEG l2, POINT &inter) 
{ 
   LINE ll1, ll2; 
   ll1 = makeline(l1.s, l1.e); 
   ll2 = makeline(l2.s, l2.e); 
   if(lineintersect(ll1, ll2, inter))
      return online(l1, inter); 
   return 0; 
}
