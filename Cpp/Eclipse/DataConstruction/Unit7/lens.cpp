#include <iostream>
#include <fstream>
#include <math.h>
#include <iomanip>
using namespace std;

const double MAXL = 1E+6;//无限远长度
const double MINU = 1E-6;//无穷小角度

struct LENS {
	double N;//透鏡的折射率
	double R1,//第一个曲面的曲率半径
			R2,//第二个曲面的曲率半径
			D;//透镜厚度
};

int main() {
	ofstream out("out.txt");
	ifstream in("in.txt");

	int i, m;
	int n;//透镜组的透镜数目
	in >> n;

	double F1, H1, F2, H2;
	LENS*Lens = new LENS[n];
	double*l = new double[2 * n + 1];//物距
	double*d = new double[2 * n - 1];//距离
	double*h = new double[2 * n + 1];//入射高度
	double*N = new double[2 * n + 1];//折射率
	double*u = new double[2 * n + 1];//入射孔径角
	double*r = new double[2 * n];//球面曲率半径

	for (i = 0; i < n; i++) {
		in >> Lens[i].R1 >> Lens[i].R2 >> Lens[i].D >> Lens[i].N;

		N[2 * i] = 1;
		N[2 * i + 1] = Lens[i].N;

		r[2 * i] = Lens[i].R1;
		r[2 * i + 1] = Lens[i].R2;

		d[2 * i] = Lens[i].D;
		if (i < n - 1)
			in >> d[2 * i + 1];
	}

	m = 2 * n;
	N[m] = 1;

	in >> h[0];
	u[0] = 0;
	l[0] = MAXL;
	for (i = 0; i < m; i++) {
		l[i + 1] = N[i + 1] / (N[i] / l[i] + (N[i + 1] - N[i]) / r[i]);
		u[i + 1] = h[i] / l[i + 1];
		if (i < m - 1) {
			l[i + 1] -= d[i];
			h[i + 1] = l[i + 1] * h[i] / (l[i + 1] + d[i]);
		}
	}

	H2 = l[m] - h[0] / u[m];//H2表示像方基点到出射顶点的距离
	F2 = l[m] - H2;//F2表示像方焦点到像方基点的距离

	out << "         l[i]        u[i]        h[i]\n";
	for (i = 0; i <= m; i++) {
		if (fabs(l[i]) < MAXL)
			out << i << setprecision(6) << setw(12) << l[i];
		else
			out << i << "        MAXL";
		if (fabs(u[i]) > MINU)
			out << setprecision(6) << setw(12) << u[i];
		else
			out << setw(12) << 0;
		if (i == m)
			out << setw(12) << "-------" << endl;
		else
			out << setprecision(6) << setw(12) << h[i] << endl;
	}
	out << "像方基点： " << setprecision(6) << H2 << endl;
	out << "像方焦距： " << setprecision(6) << F2 << endl << endl << endl << endl;

	h[m] = h[0];
	u[m] = 0;
	l[m] = MAXL;
	//l[m]=-74.2844;u[m]=-0.112182;h[m]=l[m]*u[m];
	for (i = 0; i < m; i++)
		r[i] = -r[i];
	for (i = m; i > 0; i--) {
		l[i - 1] = N[i - 1] / (N[i] / l[i] + (N[i - 1] - N[i]) / r[i - 1]);
		u[i - 1] = h[i] / l[i - 1];
		if (i > 1) {
			l[i - 1] -= d[i - 2];
			h[i - 1] = l[i - 1] * h[i] / (l[i - 1] + d[i - 2]);
		}
	}

	H1 = l[0] - h[m] / u[0];//H1表示物方基点到出射顶点的距离
	F1 = l[0] - H1;//F1表示物方焦点到出射顶点的距离

	out << "         l[i]        u[i]        h[i]\n";
	for (i = m; i > -1; i--) {
		if (fabs(l[i]) < MAXL)
			out << i << setprecision(6) << setw(12) << l[i];
		else
			out << i << "        MAXL";
		if (fabs(u[i]) > MINU)
			out << setprecision(6) << setw(12) << u[i];
		else
			out << setw(12) << 0;
		if (i == 0)
			out << setw(12) << "-------" << endl;
		else
			out << setprecision(6) << setw(12) << h[i] << endl;
	}
	out << "物方基点： " << setprecision(6) << H1 << endl;
	out << "物方焦距： " << setprecision(6) << F1 << endl;

	delete[] Lens;
	delete[] l;
	delete[] N;
	delete[] u;
	delete[] r;
	delete[] h;
	delete[] d;
	return 0;
}

