#pragma once

template<typename T>
class VectorTraits_base {
  public:
    typedef T                ValueType;
    typedef const ValueType& ReturnType;
    typedef const ValueType  ScalarType;

    inline static ValueType mult(ScalarType x, ReturnType y) { return x * y; }
    inline static ValueType value() { return 0; }
};

template<typename T>
class VectorTraits : public VectorTraits_base<T> {};

template<>
class VectorTraits<int> : public VectorTraits_base<int> {
  public:
    typedef int ValueType;
    typedef ValueType  ReturnType;
    typedef ValueType  ScalarType;
};

template<>
class VectorTraits<double> : public VectorTraits_base<double> {
  public:
    typedef double ValueType;
    typedef ValueType  ReturnType;
    typedef ValueType  ScalarType;
};

template<>
class VectorTraits<std::string> : public VectorTraits_base<std::string> {
  public:
    typedef int ScalarType;

    inline static ValueType value() { return "0"; }
    static ValueType mult(ScalarType x, ReturnType y)
    {
        ValueType temp{""};
        for (int i = 0; i < x; ++i) {
            temp += y;
        }
        return temp;
    }
};

// vim: fen
