//矩阵模板类，含有矩阵乘法，赋值，拷贝构造函数 ，幂，一元和二元加,
//一元和二元减， 转置等成员函数.
#include <iostream>
using namespace std;

template<class T>
class Matrix{
    public:
        Matrix(int r = 0, int c = 0);
        Matrix(const Matrix<T>& );
        ~Matrix() { delete [] element; }
        int Rows() const { return rows; }
        int Cols() const { return cols; }
        T& operator ()(int i, int j) ;
        Matrix<T>& operator  = (const Matrix<T>&);
        Matrix<T>& operator += (const T& x);
        Matrix<T>  Transpose   ()                    const;
        Matrix<T>  operator +  ()                    const;
        Matrix<T>  operator -  ()                    const;
        Matrix<T>  Power       (unsigned)            const;
        Matrix<T>  operator +  (const Matrix<T>&)    const;
        Matrix<T>  operator -  (const Matrix<T>&)    const;
        Matrix<T>  operator *  (const Matrix<T>&)    const;
    private:
        int rows, cols;
        T* element;
};

int main()
{
    Matrix<int> A(3,3), B(3, 4), C(3, 3);

    for(int i = 1; i < 4; i++)  {
        for(int j = 1; j < 4; j++) A(i, j) = (i + j);
        for(int j = 1; j < 4; j++) cout << A(i, j) << " ";
        cout << endl;
    }
    cout << endl;

    for(int i = 1; i < 4; i++)  {
        for(int j = 1; j < 5; j++) B(i, j) = i - j;
        for(int j = 1; j < 5; j++) cout << B(i, j) << " ";
        cout << endl;
    }
    cout << endl;

    B = A * B;
    for(int i = 1; i < 4; i++)  {
        for(int j = 1; j < 5; j++) cout << B(i, j) << " ";
        cout << endl;
    }
    cout << endl;


    for(int i = 0; i < 4; i++) {
        C = A.Power(i);
        for(int j = 1; j < 4; j++) {
            for(int k = 1; k < 4; k++) cout << C(j, k) << " ";
            cout << endl;
        }
        cout << endl;
    }
    system("pause");
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
    delete [] element;
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

//一元减法
template<class T>
Matrix<T> Matrix<T>:: operator - ()     const
{
    Matrix<T> w(rows, cols);
    for(int i = 0; i < rows * cols; i++) w.element[i] = -element[i];
    return w;
}

//二元减法
template<class T>
Matrix<T> Matrix<T>:: operator - (const Matrix<T>& m)    const
{
    Matrix<T> w(rows, cols);
    for(int i = 0; i < rows * cols; i++)
    w.element[i] = element[i] - m.element[i];
    return w;
}

//一元加法
template<class T>
Matrix<T> Matrix<T>:: operator + ()     const
{
    Matrix<T> w(rows,cols);
    for(int i = 0; i < rows * cols; i++) w.element[i] = element[i];
    return w;
}

//二元加法
template<class T>
Matrix<T> Matrix<T>:: operator + (const Matrix<T>& m)   const
{
    Matrix<T> w(rows, cols);
    for(int i = 0; i < rows * cols; i++)
    w.element[i] = element[i] + m.element[i];
    return w;
}

//自增运算符 +=
template<class T>
Matrix<T>& Matrix<T>:: operator += (const T& x)
{
    for(int i = 0; i < rows * cols; i++)
    element[i] += x;
    return *this;
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
            w.element[cw++] = sum;
            ct -= cols - 1;
            cm = j;
        }
        ct += cols;
        cm = 0;
    }
    return w;
}

//矩阵转置函数
template<class T>
Matrix<T> Matrix<T>::Transpose()    const
{
    Matrix<T> w(cols, rows);
    for(int i=1;i<=cols;i++)
    for(int j=1;j<=rows;j++) w(i,j)=(*this)(j,i);
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
