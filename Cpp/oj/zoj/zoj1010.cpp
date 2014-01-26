/**
 * @author moshangcheng
 * @version 1.0
 * @date 2011-3-25 下午02:50:51
 * @brief http://acm.zju.edu.cn/onlinejudge/showProblem.do?problemCode=1010
 */
#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

/* 常用的常量定义 */
const double INF = 1E200;
const double EP = 1E-6;
const double PI = 2 * acos(0.0);

/* 基本几何结构 */
class Point {
public:
	double x, y, length;

	Point(double a = 0, double b = 0) {
		x = a;
		y = b;
		length = 0;
	}

	Point(const Point& p) {
		x = p.x;
		y = p.y;
		length = p.length;
	}

	void operator =(const Point& p) {
		x = p.x;
		y = p.y;
		length = p.length;
	}

	// 返回两点之间欧氏距离
	double distance(const Point& p) const {
		return sqrt((x - p.x) * (x - p.x) + (y - p.y) * (y - p.y));
	}

	Point operator +(const Point& p) const {
		return Point(x + p.x, y + p.y);
	}

	Point operator -(const Point& p) const {
		return Point(x - p.x, y - p.y);
	}

	// r=multiply(b),得到 两向量的叉积
	// r>0: b在当前矢量的逆时针方向；
	// r=0：b和当前矢量共线；
	// r<0: b在当前矢量的顺时针方向
	double multiply(const Point& p) const {
		return x * p.y - y * p.x;
	}

	// r=dotmultiply(b),
	// 得到矢量点积，如果两个矢量都非零矢量
	// r<0:两矢量夹角为锐角；r=0：两矢量夹角为直角；r>0:两矢量夹角为钝角
	double dotMultiply(const Point& p) const {
		return x * p.x + y * p.y;
	}

	// 返回两个矢量的夹角的余弦(-1 --- 1)
	// 注意：如果想从余弦求夹角的话，注意反余弦函数的定义域是从 0到pi
	double cosine(const Point& b) const {
		return dotMultiply(b) / (length * b.length);
	}

	// 返回两个矢量的夹角的正弦(-1 --- 1)
	double sine(const Point& b) const {
		return multiply(b) / (length * b.length);
	}

	// 角度小于pi，返回正值
	// 角度大于pi，返回负值
	// 可以用于求线段之间的夹角 (单位：弧度)
	double angle(const Point& b) const {
		double phi = acos(cosine(b));
		if (sine(b) < 0)
			return -phi;
		return phi;
	}

	Point rotate(const Point& o, double alpha) const {
		double sinAlpha = sin(alpha);
		double cosAlpha = cos(alpha);
		Point tmp = (*this) - o;
		return Point(tmp.x * cosAlpha - tmp.y * sinAlpha + o.x, tmp.y
				* cosAlpha + tmp.x * sinAlpha + o.y);
	}
};

// 直线的解析方程 a*x+b*y+c=0 为统一表示，约定 a >= 0
class Line {
public:
	double a, b, c;
	double slope, alpha;

	Line(double d1 = 1, double d2 = -1, double d3 = 0) {
		a = d1;
		b = d2;
		c = d3;
		slope = cclSlope();
		alpha = cclAlpha();
	}

	Line(const Line& t) {
		a = t.a;
		b = t.b;
		c = t.c;
		slope = t.slope;
		alpha = t.alpha;
	}

	Line(const Point& p1, const Point& p2) {
		int sign = 1;
		a = p2.y - p1.y;
		if (a < 0) {
			sign = -1;
			a = sign * a;
		}
		b = sign * (p1.x - p2.x);
		c = sign * (p1.y * p2.x - p1.x * p2.y);
		slope = cclSlope();
		alpha = cclAlpha();
	}

	void operator =(const Line& t) {
		a = t.a;
		b = t.b;
		c = t.c;
		slope = t.slope;
		alpha = t.alpha;
	}

	// 回直线的斜率k,水平线返回 0,竖直线返回 无穷大
	double cclSlope() {
		if (fabs(a) < 1e-20)
			return 0;
		if (fabs(b) < 1e-20)
			return 2 * INF;
		return -(a / b);
	}

	// 返回直线的倾斜角alpha ( 0 - pi)
	double cclAlpha() {
		if (fabs(a) < EP)
			return 0;
		if (fabs(b) < EP)
			return PI / 2;
		double k = cclSlope();
		if (k > 0)
			return atan(k);
		else
			return PI + atan(k);
	}

	//求点p到线段l所在直线的距离
	double pointDistance(const Point& p) {
		return fabs(a * p.x + b * p.y + c) / sqrt(a * a + b * b);
	}

	// 求点p关于直线l的对称点
	Point symmetricPoint(const Point& p) const {
		return Point(((b * b - a * a) * p.x - 2 * a * b * p.y - 2 * a * c) / (a
				* a + b * b), ((a * a - b * b) * p.y - 2 * a * b * p.x - 2 * b
				* c) / (a * a + b * b));
	}

	//如果两条直线 l1(a1*x+b1*y+c1 = 0), l2(a2*x+b2*y+c2 = 0)
	//相交 1，重合 0，不相交 -1, 且返回交点p
	int LineRelation(const Line& l2, Point& p) const {
		double d = a * l2.b - l2.a * b;
		double d1 = l2.a * c - a * l2.c;
		double d2 = l2.c * b - c * l2.b;
		if (abs(d) < EP) {
			if (abs(d1) < EP)
				return 0;// 重合
			else
				return -1;// 平行
		}
		p.x = d2 / d;
		p.y = d1 / d;
		return 1;
	}
};

class LineSegment {
public:
	Point s, e, v;

	LineSegment() {
	}
	LineSegment(const Point& a, const Point& b) {
		s = a;
		e = b;
		v = b - a;
	}

	LineSegment(const LineSegment& a) {
		s = a.s;
		e = a.e;
		v = a.v;
	}

	void operator =(const LineSegment& a) {
		s = a.s;
		e = a.e;
		v = a.v;
	}

	LineSegment rotate(const Point& o, double alpha) const {
		return LineSegment(s.rotate(o, alpha), e.rotate(o, alpha));
	}

	/*
	 * 判断点与线段的关系,用途很广泛 本函数是根据下面的公式写的，P是点C到线段AB所在直线的垂足
	 * 		AC dot AB
	 * r = ---------
	 * 		||AB||^2
	 *
	 * 	 (Cx-Ax)(Bx-Ax) + (Cy-Ay)(By-Ay)
	 * = -------------------------------
	 * 			L^2
	 *
	 * r has the following meaning:
	 *
	 * r=0 P = A
	 * r=1 P = B
	 * r<0 P is on the backward extension of AB
	 * r>1 P is on the forward extension of AB
	 * 0<r<1 P is interior to AB
	 */
	double pointRelation(const Point& p) const {
		return v.dotMultiply(p - s) / v.length;
	}

	// 判断点p是否在线段l上，
	//条件：(p在线段l所在的直线上)&& (点p在以线段l为对角线的矩形内)
	bool containsPoint(const Point& p) const {
		LineSegment ls1(s, p);
		LineSegment ls2(e, p);
		if (fabs(ls1.v.multiply(ls2.v)) > EP)
			return false;
		//包含等于0，即与端点重合的情况
		if (ls1.v.x * ls2.v.x > EP)
			return false;
		if (ls1.v.y * ls2.v.y > EP)
			return false;
		return true;
	}

	// 求点C到线段AB所在直线的垂足 P
	Point pointPerpendicular(const Point& p) const {
		double r = pointRelation(p);
		return Point(s.x + r * v.x, s.y + r * v.y);
	}

	// 返回线段上距该点最近的点np
	//注意：np是线段l上到点p最近的点，不一定是垂足
	Point nearestPoint(const Point& p) const {
		double r = pointRelation(p);
		if (r < 0) {
			return s;
		} else if (r > 1) {
			return e;
		} else {
			return pointPerpendicular(p);
		}
	}

	//判断线段 u 是否与直线 l 相交
	//重合 0， 相交 1， 不相交 -1
	int LineRelation(const Line& l, Point& p) {
		Line tmp(s, e);
		double r = tmp.LineRelation(l, p);
		if (r == 0)
			return 0;
		else if (r == 1) {
			if (containsPoint(p))
				return 1;
			else
				return -1;
		}
		return -1;
	}

	//线段和线段的关系:  不相交不共线 -2， 不相交但共线 -1
	//相交但不共线 2， 相交且共线 1， 重合 0
	int LineSegmentRelation(const LineSegment& ls, Point& p) const {
		Line l1(s, e);
		Line l2(ls.s, ls.e);
		int r = l1.LineRelation(l2, p);
		if (s.distance(ls.s) < EP && e.distance(ls.e) < EP)
			return 0;
		if (r == 0) {
			if (ls.containsPoint(s) || ls.containsPoint(e))
				return 1;
			else
				return -1;
		} else if (r == 1) {
			if (containsPoint(p) && ls.containsPoint(p))
				return 2;
			else
				return -2;
		} else
			return -2;
	}
};

class Circle {
public:
	Point center;
	double radius;

	Circle() {
		radius = 0;
	}

	Circle(double r, Point c) {
		radius = r;
		center = c;
	}

	Circle(const Circle& circle) {
		radius = circle.radius;
		center = circle.center;
	}

	void operator =(const Circle& circle) {
		radius = circle.radius;
		center = circle.center;
	}
};

class Polygon {
public:
	vector<Point> Points;

	Polygon() {
	}

	Polygon(const vector<Point>& ps) {
		Points = ps;
	}

	Polygon(const Polygon& p) {
		for (int i = 0; i < p.Points.size(); i++) {
			Points.push_back(p.Points[i]);
		}
	}

	//计算点到多边形的最近点.
	Point nearestPoint(const Point& p) const {
		Point minPoint, cntPoint;
		double minDistance = INF, cntDistance;

		for (int i = 1; i <= Points.size(); i++) {
			LineSegment tmp(Points[i - 1], Points[i % Points.size()]);
			cntPoint = tmp.nearestPoint(p);
			cntDistance = cntPoint.distance(p);
			if (cntDistance < minDistance) {
				minDistance = cntDistance;
				minPoint = cntPoint;
			}
		}
		return minPoint;
	}

	//判断圆是否在多边形内
	bool containsCircle(const Circle& circle) const {
		double d = nearestPoint(circle.center).distance(circle.center);
		if (d - circle.radius < EP)
			return true;
		else
			return false;
	}

	//计算多边形的面积
	double area() const {
		double sum = 0;
		for (int i = 0; i < Points.size(); i++) {
			sum += Points[i].multiply(Points[(i + 1) % Points.size()]) / 2.0;
		}
		return fabs(sum);
	}
};

int main() {
	int n = 0;
	for (int number = 1; scanf("%d", &n) == 1; number++) {
		if (n == 0) {
			break;
		}
		Polygon polygon;
		vector<Point> Points;
		vector<LineSegment> Segs;
		for (int i = 0; i < n; i++) {
			double tempX, tempY;
			scanf("%lf%lf", &tempX, &tempY);
			Points.push_back(Point(tempX, tempY));
		}
		for (int i = 0; i < n; i++) {
			Segs.push_back(LineSegment(Points[i], Points[(i + 1) % n]));
		}
		polygon = Polygon(Points);

		if (number > 1)
			printf("\n");
		printf("Figure %d: ", number);
		if (n < 3) {
			printf("Impossible\n");
			continue;
		}
		bool success = true;
		;
		for (int i = 0; i < n && success; i++) {
			Point p;
			for (int j = 0; j + 1 < i && success; j++) {
				if (Segs[i].LineSegmentRelation(Segs[j], p) >= 0) {
					if (!(i == n - 1 && j == 0))
						success = false;
				}
			}
		}
		if (success) {
			printf("%.2lf\n", polygon.area());
		} else {
			printf("Impossible\n");
		}
	}
	return 0;
}

