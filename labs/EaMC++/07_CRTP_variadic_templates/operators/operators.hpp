#pragma once

template<int N> class Vector;

template<typename L, typename R>
class Vector_lazy {
  public:
    using F = int (*)(L,R,int);

    Vector_lazy(L&& left_, R&& right_, F op_) :
        left(std::forward<L>(left_)), right(std::forward<R>(right_)), op(op_)
    {}

    int operator [](int n)
    {
        return op(left, right, n);
    }

    template<int N>
    operator Vector<N>()
    {
        Vector<N> temp;
        for (int i = 0; i < N; ++i) {
            temp[i] = (*this)[i];
        }
        return temp;
    }

  private:
    L left;
    R right;
    F op;
};

template<typename L, typename R>
Vector_lazy<L,R> operator +(L&& l, R&& r)
{
    return Vector_lazy<L,R>(std::forward<L>(l), std::forward<R>(r),
        [](L l, R r, int n) { return l[n] + r[n]; });
}

template<typename L, typename R>
Vector_lazy<L,R> operator -(L&& l, R&& r)
{
    return Vector_lazy<L,R>(std::forward<L>(l), std::forward<R>(r),
        [](L l, R r, int n) { return l[n] - r[n]; });
}

template<typename L, typename R>
Vector_lazy<L,R> operator *(L&& l, R&& r)
{
    return Vector_lazy<L,R>(std::forward<L>(l), std::forward<R>(r),
        [](L l, R r, int n) { return l * r[n]; });
    // ^ I've assumed scalar is always first
}

// vim: fen fdl=1
