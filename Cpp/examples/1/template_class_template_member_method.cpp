//template<typename T1> template<typename T2>

template <typename T>
class FloatImpl
{
    template<class G>
    inline FloatImpl<T>& operator%=( FloatImpl<G> const &f );


};

template<typename T>  template< class V>
inline FloatImpl<T>& FloatImpl<T>::operator%=( FloatImpl<V> const &f ) { return *this; }


class TS {
    template<typename T> void f();
};

template<typename T> void TS::f() {}

int main() {
    return 0;
}
