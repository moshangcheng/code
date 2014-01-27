#include <iomanip>
#include <iostream>
using namespace std;


double sqrt(double a)
{
    double x0, x1; //函数内局部变量
    x0= 1e-8; // 1/sqrt(a)近似值
    x1= (3*x0 - a * x0*x0*x0) * 0.5;
    while (x1-x0 >1e-10)  {
        //每迭代一次，精度提高一倍，如这次精确到3位，则下次精确到6位，再次精确到12位，
        x0 = x1;
        x1 = (3*x0 - a * x0*x0*x0) * 0.5;  
    }
   // 计算sqrt(a)
   return a*x1;
}


int main()
{
    double x;
    while(1)  {
        cout << "Please input a real number\n";
        cin >> x;
        cout.setf(ios::fixed);
        cout << setprecision(16) << sqrt(x) << endl;   
    }
}
