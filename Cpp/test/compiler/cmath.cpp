//C++中只有头文件<cmath>,而没有<math> 
#include <iostream>
#include <cmath>
#include <ctime>
using namespace std;

int main()
{
    /*double x,frac_part,int_part;
    cout<<"请输入一个实数\n"; 
    cin>>x;    
    frac_part=modf(x,&int_part);
    cout<<"Integer part of "<<x<<" is: "<<int_part<<endl;
    cout<<"Fraction part of "<<x<<" is: "<<frac_part<<endl;
    cout<<endl<<endl;
    
    double base,exp;
    cout<<"请输入指数的底: "<<endl;
    cin>>base;
    cout<<"请输入指数的幂: \n";
    cin>>exp;
    cout<<"以 "<<base<<" 为底, 以 "<<exp<<" 为幂的数是 "<<pow(base,exp)<<endl;
    cout<<endl; 
    
    //abs()是求整数的绝对值，fabs()是求实数的绝对值
    int i;
    double f;
    cout<<"请输入一个整数\n";
    cin>>i;
    cout<<i<<" 的绝对值是 "<<abs(i)<<endl;
    cout<<"请输入一个实数\n";
    cin>>f;
    cout<<f<<" 的绝对值是 "<<fabs(f)<<endl;
    cout<<endl; 
     
    double a,b;
    cout<<"Please input a real number: ";
    cin>>a;
    cout<<"Please input another real number: ";
    cin>>b;
    cout<<"the remainder of "<<a<<'/'<<b<<" is "<<fmod(a,b)<<endl;
    
    double num,coef;
    int exp;
    cout<<"Please input a real number: ";
    cin>>num;
    coef=frexp(num,&exp);
    cout<<num<<" = "<<coef<<" * "<<"2^"<<exp<<endl;
    
    double x;
    cout<<"Please input a real number: ";
    cin>>x;
    cout<<"log10("<<x<<") = "<<log10(x)<<endl;
    cout<<"log("<<x<<") = "<<log(x)<<endl;
    cout<<"log2("<<x<<") = "<<log2(x)<<endl;
    
    srand( time(NULL) );
    cout<<RAND_MAX<<endl;
    for(int i=0;i<10;i++)
    cout<<"Random number #"<<i+1<<" : "<<rand()<<endl;     
    cout<<endl;
    
    //cout<<"Current time is: "<<*asctime(NULL)<<endl;
    cout<<"Current time is: "<<time(NULL)<<endl;
    cout<<CLOCKS_PER_SEC<<endl;
    //cout<<"Current time is: "<<localtime(&time(NULL))<<endl;*/
    
    //while(1)
    //cout<<'\a';
    
    cout << ceil(-1.1) << " " << floor(-1.1) << endl;
    system("pause");
    return 0;
}
