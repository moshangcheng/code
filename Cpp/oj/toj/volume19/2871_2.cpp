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
        T& operator ()(int i, int j) 
        { return element[ (i - 1) * cols + j - 1]; }
        Matrix<T>& operator = (const Matrix<T>&);
        Matrix<T>  operator * (const Matrix<T>&) const;
    private:
        int rows, cols;
        T* element;
};    


template<class T>
Matrix<T> Power(Matrix<T> A, unsigned p)
{
    Matrix<T> E(A.Rows(), A.Cols());
    for(int i = 1; i <= E.Rows(); i++) E(i, i) = 1;
    if(p == 0) return E;
    while(p > 1) {
        if(p & 1 == 1) E = E * A;
        A = A * A;
        p /= 2;
    }
    return A * E;
}
    
int main()
{
    int N, M, S, i, j, v1, v2;
    while(cin >> N >> M) {
        Matrix<int> A(N, N), B(1, 2*N), C(2*N, 1), T(2*N, 2*N);
        if(N == 0 && M == 0) break;
        for(i = 0; i < M; i++) {
            cin >> v1 >> v2;
            A(v1, v2) = A(v2, v1) = 1;
        }
        for(i = 1; i <= N; i++) A(i, i) = 1;
        cin >> S;
        B(1, 1) = 1;
        for(i = 1; i <= N; i++) C(i, 1) = 1;
        for(i = 1; i <= N; i++) B(1, i + N) = A(1, i);       
        for(i = 1; i <= N; i++) {
            T(i, i) = T(i + N, i) = 1;
            for(j = 1; j <= N; j++) T(N + i,N + j) = A(i, j);
        }
                
        T = Power(T, S);
        B = B * T * C;
        cout << B(1, 1) << endl;
    }
    return 0;
}

template<class T>
Matrix<T>:: Matrix(int r, int c)
{
    rows = r;  cols = c;
    element = new T[r*c];
    memset(element, 0, sizeof(element) * r *c);
}

template<class T>
Matrix<T>:: Matrix(const Matrix<T>& m)
{
    rows = m.rows;
    cols = m.cols;
    element = new T[rows*cols];
    for(int i  =0; i < rows * cols; i++) element[i] = m.element[i];
}

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
            sum = sum % 2007;
            w.element[cw++] = sum;
            ct -= cols - 1;
            cm = j;
        }
        ct += cols;
        cm = 0;
    }
    return w;
}                
            
        
        
    
    
    
