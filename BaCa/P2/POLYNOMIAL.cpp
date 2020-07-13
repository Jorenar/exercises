// Jakub Lukasiewicz

// 43% ...

namespace helpers {

  template<typename T>
  inline T max(T a, T b)
  {
      return a > b ? a : b;
  }

  template<typename T>
  inline T min(T a, T b)
  {
      return a < b ? a : b;
  }

  template<typename T>
  inline T gcd(T a, T b)
  {
      if (a == 0) {
          return b;
      }
      if (b == 0) {
          return a;
      }
      int temp;
      while (b != 0) {
          temp = a % b;
          a = b;
          b = temp;
      }
      return a;
  }

  template<typename T>
  inline T LCM(T a, T b)
  {
      if (a < 0) {
          a = -a;
      }
      if (b < 0) {
          b = -b;
      }
      return (a*b) / helpers::gcd(a, b);
  }

  template<typename T>
  struct Fraction {
      T numerator;
      T denominator;
      Fraction() : numerator(0), denominator(1) {}
      Fraction(const Fraction& obj) : numerator(obj.numerator), denominator(obj.denominator) {}

      void reduce()
      {
          long long g = helpers::gcd(numerator, denominator);
          if (g < 0) { g = -g; }
          numerator   /= g;
          denominator /= g;
      }

      Fraction<T> operator *(const Fraction& obj)
      {
          Fraction<T> temp(*this);
          temp.numerator   *= obj.numerator;
          temp.denominator *= obj.denominator;
          return temp;
      }

      Fraction<T> operator *=(const Fraction& obj)
      {
          *this = (*this) * obj;
          return *this;
      }

      Fraction& operator =(const T& number)
      {
          numerator   = number;
          denominator = 1;
          return *this;
      }

  };

  template<typename T>
  class Vector {
      long long N;
      size_t capacity;
      T* data;

    public:
      Vector(size_t n = 10) : N(0), capacity(n), data(new T[n]) {}

      Vector(const Vector& obj) : N(obj.N), data(new T[N])
      {
          for (size_t i = 0; i < N; ++i) {
              data[i] = obj.data[i];
          }
      }

      ~Vector() { delete[] data; }

      void pushBack(T elem)
      {
          if (N >= capacity) {
              resize(2 * N);
          }
          data[N] = elem;
          ++N;
      }

      T popBack()
      {
          --N;
          return data[N+1];
      }

      void remove(size_t n)
      {
          for (size_t i = n; i < N - 1; ++i) {
              data[i] = data[i+1];
          }
          if (N > 0) {
              --N;
          }
      }

      Vector& operator =(const Vector& obj)
      {
          if (this != &obj) {
              if (data) {
                  delete[] data;
              }
              N = obj.N;
              data = new T[N];
              for (size_t i = 0; i < N; ++i) {
                  data[i] = obj.data[i];
              }
          }
          return *this;
      }

      void resize(size_t n)
      {
          if (n == 0) {
              if (data) {
                  delete[] data;
                  data = NULL;
              }
              capacity = 10;
          }
          else if (n > capacity) {
              T* temp = new T[n];
              for (size_t i = 0; i < N; ++i) {
                  temp[i] = data[i];
              }
              for (size_t i = N; i < n; ++i) {
                  temp[i] = 0;
              }
              delete[] data;
              data = temp;
              capacity = n;
          }
          else if (3*n < capacity) {
              T* temp = new T[n];
              if (n > N) {
                  n = N;
              }
              for (size_t i = 0; i < n; ++i) {
                  temp[i] = data[i];
              }
              delete[] data;
              data = temp;
              capacity = 2*n;
          }
      }

      void setSize(size_t n)
      {
          N = n;
      }

      long long size() const
      {
          return N > 0 ? N : 0;
      }

      void reset(size_t n = 10)
      {
          if (data) {
              delete[] data;
          }
          N = 0;
          data = new T[n];
          capacity = n;
      }

      T operator [](size_t n) const
      {
          return data[n];
      }

      T& operator [](size_t n)
      {
          return data[n];
      }

      Vector operator -()
      {
          Vector temp(*this);
          for (size_t i = 0; i < N; ++i) {
              temp.data[i] *= -1;
          }
          return temp;
      }

  };

  template<typename T>
  bool operator ==(const Vector<T>& v1, const Vector<T>& v2)
  {
      if (v1.size() == v2.size()) {
          for (size_t i = 0; i < v1.size(); ++i) {
              if (v1[i] != v2[i]) {
                  return false;
              }
          }
          return true;
      }
      return false;
  }

  template<typename T>
  bool operator !=(const Vector<T>& v1, const Vector<T>& v2)
  {
      return !(v1 == v2);
  }

}

class POLYNOMIAL {
    typedef helpers::Vector<int> Vec;
    Vec data;
    void reduce(int);

  public:
    static int overloaded;

    POLYNOMIAL() {}
    POLYNOMIAL(const Vec& v) : data(v) {}
    POLYNOMIAL(int n, ...);
    POLYNOMIAL(const POLYNOMIAL& obj) : data(obj.data) {}

    int  at(size_t n) const;
    int& at(size_t n);

    const size_t deg() const;

    POLYNOMIAL operator -();
    POLYNOMIAL operator +(const POLYNOMIAL&);
    POLYNOMIAL operator -(const POLYNOMIAL&);
    POLYNOMIAL operator *(const POLYNOMIAL&);
    POLYNOMIAL operator >>(long long n);
    POLYNOMIAL operator <<(long long n);
    POLYNOMIAL operator /(const POLYNOMIAL& poly);
    POLYNOMIAL operator %(const POLYNOMIAL& poly);

    POLYNOMIAL& operator +=(const POLYNOMIAL& poly);
    POLYNOMIAL& operator -=(const POLYNOMIAL& poly);
    POLYNOMIAL& operator *=(const POLYNOMIAL& poly);
    POLYNOMIAL& operator /=(const POLYNOMIAL& poly);
    POLYNOMIAL& operator %=(const POLYNOMIAL& poly);
    POLYNOMIAL& operator <<=(long long n);
    POLYNOMIAL& operator >>=(long long n);

    POLYNOMIAL& operator ++();
    POLYNOMIAL operator ++(int);
    POLYNOMIAL& operator --();
    POLYNOMIAL operator --(int);

    void* operator new(size_t);
    void operator delete(void*);

    friend bool operator  <(const POLYNOMIAL&, const POLYNOMIAL&);
    friend bool operator <=(const POLYNOMIAL&, const POLYNOMIAL&);
    friend bool operator ==(const POLYNOMIAL&, const POLYNOMIAL&);
    friend bool operator >=(const POLYNOMIAL&, const POLYNOMIAL&);
    friend bool operator  >(const POLYNOMIAL&, const POLYNOMIAL&);
    friend bool operator !=(const POLYNOMIAL&, const POLYNOMIAL&);

    friend std::ostream& operator <<(std::ostream&, const POLYNOMIAL&);
    friend std::istream& operator >>(std::istream&, POLYNOMIAL&);

};

POLYNOMIAL::POLYNOMIAL(int n, ...)
{
    if (n >= 0) {
        va_list args;
        va_start(args, n);

        int g = 0; // gcd

        for (int i = 0; i <= n; ++i) {
            data.pushBack(va_arg(args, int));
            g = helpers::gcd(g, at(i));
        }

        reduce(g);
        va_end(args);
    }
}

// helper methods {{{

void POLYNOMIAL::reduce(int g)
{
    if (data.size() == 0) {
        return;
    }

    if (g == 0) {
        g = 1;
    }
    else if (g < 0) {
        g = -g;
    }

    size_t n = data.size() - 1;
    while (n > 0) {
        if (at(n) == 0) {
            --n;
        }
        else {
            break;
        }
    }
    data.resize(n+1);
    data.setSize(n+1);

    for (size_t i = 0; i < data.size(); ++i) {
        at(i) /= g;
    }
}

int POLYNOMIAL::at(size_t n) const
{
    return data[n];
}

int& POLYNOMIAL::at(size_t n)
{
    return data[n];
}

const size_t POLYNOMIAL::deg() const
{
    return data.size() > 0 ? data.size() - 1 : 0;
}

// ~ helper methods }}}

// Math operators {{{

POLYNOMIAL POLYNOMIAL::operator -()
{
    return POLYNOMIAL(-data);
}

POLYNOMIAL POLYNOMIAL::operator +(const POLYNOMIAL& obj)
{
    size_t n = helpers::max(data.size(), obj.data.size());

    POLYNOMIAL temp;

    int g = 0; // gcd

    for (size_t i = 0; i < n; ++i) {
        temp.data.pushBack(0);

        if (i < data.size()) {
            temp.at(i) += at(i);
        }
        if (i < obj.data.size()) {
            temp.at(i) += obj.at(i);
        }

        g = helpers::gcd(g, temp.at(i));
    }

    temp.reduce(g);

    return temp;

}

POLYNOMIAL POLYNOMIAL::operator -(const POLYNOMIAL& obj)
{
    size_t n = helpers::max(data.size(), obj.data.size());

    POLYNOMIAL temp;

    int g = 0; // gcd

    for (size_t i = 0; i < n; i++ ) {
        temp.data.pushBack(0);

        if (i < data.size()) {
            temp.at(i) += at(i);
        }
        if (i < obj.data.size()) {
            temp.at(i) -= obj.at(i);
        }

        g = helpers::gcd(g, temp.at(i));
    }

    temp.reduce(g);

    return temp;

}

POLYNOMIAL POLYNOMIAL::operator *( const POLYNOMIAL& obj)
{
    int n = data.size() + obj.data.size() - 1;
    int g = 0; // gcd

    POLYNOMIAL temp;

    for (int i = 0; i < n; ++i) {
        temp.data.pushBack(0);
    }

    for (size_t i = 0; i < data.size(); ++i) {
        for (size_t j = 0; j < obj.data.size(); ++j) {
            temp.at(i+j) += at(i) * obj.at(j);
        }
    }

    for (int i = 0; i < n; ++i) {
        g = helpers::gcd(g, temp.at(i));
    }

    temp.reduce(g);

    return temp;
}

POLYNOMIAL POLYNOMIAL::operator /(const POLYNOMIAL& obj)
{
    POLYNOMIAL result;

    if (data.size() > 0) {
        if (obj.deg() == 0) {
            if (obj.at(0) == 0) {
                return result;
            }
            int g = 0;
            for (size_t i = 0; i < data.size(); ++i) {
                result.data.pushBack(at(i) / obj.at(0));
                g = helpers::gcd(g, result.at(i));
            }
            result.reduce(g);
        }
        else if (deg() >= obj.deg()) {

            size_t resultSize = data.size() - obj.data.size() + 1;
            helpers::Fraction<int>* resultCoefficients = new helpers::Fraction<int>[resultSize];

            helpers::Fraction<int>* temp1 = new helpers::Fraction<int>[data.size()];
            helpers::Fraction<int>* temp2 = new helpers::Fraction<int>[data.size()];

            for (size_t i = 0; i < data.size(); ++i) {
                temp1[i] = at(i);
            }

            long long degTemp = deg();

            while (degTemp >= obj.deg()) {

                long long I = degTemp - obj.deg();

                for (size_t i = 0; i < obj.data.size(); ++i) {
                    temp2[i + I] = obj.at(i);
                }

                resultCoefficients[I].numerator   = temp1[degTemp].numerator   * temp2[degTemp].denominator;
                resultCoefficients[I].denominator = temp1[degTemp].denominator * temp2[degTemp].numerator;

                resultCoefficients[I].reduce();

                for (size_t i = 0; i < data.size(); ++i) {
                    temp2[i] *= resultCoefficients[I];
                    temp2[i].reduce();
                }

                for (size_t i = 0; i < degTemp + 1; ++i) {
                    long long l = helpers::LCM(temp1[i].denominator, temp2[i].denominator);
                    if (l < 0) {
                        l = -l;
                    }

                    temp1[i].numerator = ((l / temp1[i].denominator) * temp1[i].numerator) - ((l / temp2[i].denominator) * temp2[i].numerator);
                    temp1[i].denominator = l;

                    temp1[i].reduce();
                }

                --degTemp;
            }

            int l = 1; // LCM
            int g = 0; // gcd

            for (size_t i = 0; i < resultSize; ++i) {
                l = helpers::LCM(l, resultCoefficients[i].denominator);
            }
            if (l < 0) {
                l = -l;
            }

            for (size_t i = 0; i < resultSize; ++i) {
                result.data.pushBack((l / resultCoefficients[i].denominator) * resultCoefficients[i].numerator);
                g = helpers::gcd(g, result.at(i));
            }

            delete[] temp1;
            delete[] temp2;
            delete[] resultCoefficients;

            result.reduce(g);
        }
    }

    return result;
}

POLYNOMIAL POLYNOMIAL::operator %(const POLYNOMIAL& obj)
{
    POLYNOMIAL result;

    if (data.size() > 0) {
        if (obj.deg() == 0) {
            if (obj.data.size() == 0) {
                return *this;
            }
            else if (obj.at(0) == 0) {
                return result;
            }
            return POLYNOMIAL(0, at(0) % obj.at(0));
        }
        else if (deg() >= obj.deg()) {

            helpers::Fraction<int>* res = new helpers::Fraction<int>[data.size()];

            helpers::Fraction<int>* temp1 = new helpers::Fraction<int>[data.size() - obj.data.size() + 1];
            helpers::Fraction<int>* temp2 = new helpers::Fraction<int>[data.size()];

            for (size_t i = 0; i < data.size(); ++i) {
                res[i] = at(i);
            }

            long long degRes = deg();

            while (degRes >= obj.deg()) {

                long long I = degRes - obj.deg();

                for (size_t i = 0; i < obj.data.size(); ++i) {
                    temp2[i + I] = obj.at(i);
                }

                temp1[I].numerator   = res[degRes].numerator   * temp2[degRes].denominator;
                temp1[I].denominator = res[degRes].denominator * temp2[degRes].numerator;

                temp1[I].reduce();

                for (size_t i = 0; i < data.size(); ++i) {
                    temp2[i] *= temp1[I];
                    temp2[i].reduce();
                }

                for (size_t i = 0; i < degRes + 1; ++i) {
                    long long l = helpers::LCM(res[i].denominator, temp2[i].denominator);
                    if (l < 0) {
                        l = -l;
                    }

                    res[i].numerator = ((l / res[i].denominator) * res[i].numerator) - ((l / temp2[i].denominator) * temp2[i].numerator);
                    res[i].denominator = l;

                    res[i].reduce();
                }

                --degRes;
            }

            int l = 1; // LCM
            for (size_t i = 0; i < degRes + 1; ++i) {
                l = helpers::LCM(l, res[i].denominator);
            }
            if (l < 0) {
                l = -l;
            }

            int g = 0; // gcd
            for (size_t i = 0; i < degRes + 1; ++i) {
                result.data.pushBack((l / res[i].denominator) * res[i].numerator);
                g = helpers::gcd(g, result.at(i));
            }

            delete[] temp1;
            delete[] temp2;
            delete[] res;

            result.reduce(g);

        }
        else {
            result = (*this);
        }
    }

    return result;
}

POLYNOMIAL& POLYNOMIAL::operator +=(const POLYNOMIAL& obj)
{
    *this = (*this) + obj;
    return *this;
}

POLYNOMIAL& POLYNOMIAL::operator -=(const POLYNOMIAL& obj)
{
    *this = (*this) - obj;
    return *this;
}

POLYNOMIAL& POLYNOMIAL::operator *=(const POLYNOMIAL& obj)
{
    *this = (*this) * obj;
    return *this;
}

POLYNOMIAL& POLYNOMIAL::operator /=(const POLYNOMIAL& obj)
{
    *this = (*this) / obj;
    return *this;
}

POLYNOMIAL& POLYNOMIAL::operator %=(const POLYNOMIAL& obj)
{
    *this = (*this) % obj;
    return *this;
}

// ~ Math operators }}}

// Shift operators {{{

POLYNOMIAL POLYNOMIAL::operator >>(long long n)
{
    if ( n == 0 || data.size() == 0 ) {
        return *this;
    }

    POLYNOMIAL temp;

    if (n > 0) {
        for (size_t i = 0; i < data.size() + n; ++i) {
            temp.data.pushBack(0);
        }

        for (size_t i = 0; i < data.size(); ++i) {
            temp.at(n+i) = at(i);
        }
    }

    return temp;
}

POLYNOMIAL POLYNOMIAL::operator <<(long long n)
{
    if (n == 0 || data.size() == 0) {
        return *this;
    }

    POLYNOMIAL temp;

    if (n > 0 && n < data.size()) {
        int g = 0;
        for (size_t i = n; i < data.size(); ++i) {
            temp.data.pushBack(at(i));
            g = helpers::gcd(g, at(i));
        }
        temp.reduce(g);
    }

    return temp;
}

POLYNOMIAL& POLYNOMIAL::operator <<=(long long n)
{
    *this = (*this) << n;
    return *this;
}

POLYNOMIAL& POLYNOMIAL::operator >>=(long long n)
{
    *this = (*this) >> n;
    return *this;
}

// ~ Shift operators }}}

// Incrementation and decrementation operators {{{

POLYNOMIAL& POLYNOMIAL::operator ++()
{
    int g = 0;
    for (size_t i = 0; i < data.size(); ++i) {
        at(i)++;
        g = helpers::gcd(g, at(i));
    }
    reduce(g);
    return (*this);
}

POLYNOMIAL POLYNOMIAL::operator ++(int)
{
    POLYNOMIAL temp(*this);
    ++(*this);
    return temp;
}

POLYNOMIAL& POLYNOMIAL::operator --()
{
    int g = 0;
    for (size_t i = 0; i < data.size(); ++i) {
        at(i)--;
        g = helpers::gcd(g, at(i));

    }
    reduce(g);
    return (*this);
}

POLYNOMIAL POLYNOMIAL::operator --(int)
{
    POLYNOMIAL temp(*this);
    --(*this);
    return temp;
}

// ~ in/decrement operators }}}

// Memory operators {{{

void* POLYNOMIAL::operator new(size_t n)
{
    ++overloaded;
    return new char[n];
}

void POLYNOMIAL::operator delete(void* p)
{
    --overloaded;
    delete p;
}

// ~ Memory operators }}}

// Relation operators {{{

bool operator ==(const POLYNOMIAL& p1, const POLYNOMIAL& p2)
{
    if (p1.data.size() > 0 && p2.data.size() > 0) {
        return p1.data == p2.data;
    }
    return p1.data.size() == p2.data.size();
}

bool operator !=(const POLYNOMIAL& p1, const POLYNOMIAL& p2)
{
    return !(p1 == p2);
}

bool operator <(const POLYNOMIAL& p1, const POLYNOMIAL& p2)
{
    if (p1.data.size() > 0 && p1.data.size() == p2.data.size()) {
        for (long long i = p1.data.size() - 1; i >= 0; --i) {
            if (p1.at(i) >= p2.at(i)) {
                return false;
            }
        }
        return true;
    }
    else {
        return p1.data.size() < p2.data.size();
    }
}

bool operator <=(const POLYNOMIAL& p1, const POLYNOMIAL& p2)
{
    return (p1 == p2) || (p1 < p2);
}

bool operator >(const POLYNOMIAL& p1, const POLYNOMIAL& p2)
{
    return (p1 != p2 && !(p1 < p2));
}

bool operator >=(const POLYNOMIAL& p1, const POLYNOMIAL& p2)
{
    return !(p1 < p2);
}

// ~ Relation operators }}}

// I/O operators {{{

std::ostream& operator <<(std::ostream& out, const POLYNOMIAL& obj)
{
    out << "(";
    if (obj.data.size() == 0) {
        out << " 0";
    }
    else {
        for (size_t i = 0; i < obj.data.size(); i++) {
            out << " " << obj.at(i);
            if (i != obj.data.size() - 1) {
                out << ",";
            }
        }
    }
    out << " )";
    return out;
}

std::istream& operator >>(std::istream& in, POLYNOMIAL& obj)
{
    size_t n;
    in >> n;

    if (n >= 0) {
        int g = 0;
        obj.data.reset();
        int temp;
        for (size_t i = 0; i <= n; ++i) {
            in >> temp;
            obj.data.pushBack(temp);
            g = helpers::gcd(g, obj.at(i));
        }
        obj.reduce(g);
    }

    return in;
}

// ~ I/O operators }}}

// vim: fen
