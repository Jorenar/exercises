#pragma once

template< template<typename, size_t, size_t> class C, typename T, size_t N, size_t M>
C<T,M,N> transpose(const C<T,N,M>& obj)
{
    C<T,M,N> temp(obj.numberOfColumns(), obj.numberOfRows(), 1);
    for (size_t i = 1; i <= obj.numberOfRows(); i++) {
        for (size_t j = 1; j <= obj.numberOfColumns(); j++) {
            temp(j,i) = obj(i,j);
        }
    }
    return temp;
}
