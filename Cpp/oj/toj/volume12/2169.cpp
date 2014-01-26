#include <iostream>
using namespace std;
 
template<class T>
class Matrix{
    public:
        Matrix(int r = 0, int c = 0);
        Matrix(const Matrix<T>& );
        ~Matrix() { delete [] element; }
        T& operator ()(int i, int j) ;
        Matrix<T>& operator  = (const Matrix<T>&);
        Matrix<T>  Power       (unsigned)            const;
        Matrix<T>  operator *  (const Matrix<T>&)    const;
    private:
        int rows, cols;
        T* element;
};    

int main()
{
    int a0, a1, n, x, y;
    Matrix<int> T(2, 2), A(2, 1), B;
    while(cin >> x >> y)  {
        if(x == 0 && y == 0) break;
        cin >> a0 >> a1 >> n;
        A(1, 1) = a1;   A(2, 1) = a0;
        T(1, 1) = x;    T(1, 2) = y;
        T(2, 1) = 1;    T(2, 2) = 0;
        B = T.Power(n) * A;
        if(B(2, 1) < 10) cout << 0;
        cout << B(2, 1) << endl;
    }
    return 0;
}      


//构造函数，矩阵中所有元素初始化为0 
template<class T>
Matrix<T>:: Matrix(int r, int c)
{
    rows = r;  cols = c;
    element = new T[r*c];
    memset(element, 0, sizeof(element)*r*c);
}

//拷贝构造函数 
template<class T>
Matrix<T>:: Matrix(const Matrix<T>& m)
{
    rows = m.rows;
    cols = m.cols;
    element = new T[rows*cols];
    for(int i  =0; i < rows * cols; i++) element[i] = m.element[i];
}

//重载()运算符 
template<class T>
T& Matrix<T>:: operator()(int i, int j)
{
    return element[ (i - 1)  *cols + j - 1];
}

//重载赋值运算符 
template<class T>
Matrix<T>& Matrix<T>:: operator = (const Matrix<T>& m)
{
    delete [] element;
    rows = m.rows;
    cols = m.cols;
    element = new T[rows*cols];
    for(int i = 0; i < rows * cols; i++) element[i] = m.element[i];
    return *this;
}

//矩阵乘法 
template<class T>
Matrix<T> Matrix<T>:: operator * (const Matrix<T>& m) const
{
    Matrix<T> w(rows, m.cols);
    int ct = 0, cm = 0, cw = 0;
    for(int i = 1;i <= rows; i++){
        for(int j = 1; j <= m.cols; j++){
            T sum = element[ct] * m.element[cm];
            for(int k = 2; k <= cols; k++){
                ct++;
                cm += m.cols;
                sum += element[ct] * m.element[cm];
            }
            w.element[cw++] = sum % 100;
            ct -= cols - 1;
            cm = j;
        }
        ct += cols;
        cm = 0;
    }
    return w;
}                
    
//矩阵幂函数 
template<class T>
Matrix<T> Matrix<T>:: Power(unsigned p) const
{
    Matrix<T> C(*this), M(rows, cols);
    for(int i =1; i <= rows; i++) M(i, i) = 1;
    if(p == 0) return M;
    while(p > 1) {
        if(p & 1 == 1) M = M * C;
        C = C * C;
        p /= 2;
    }
    return M * C;
}
