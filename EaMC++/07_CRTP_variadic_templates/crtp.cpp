#include <iostream>

namespace total {

class Counter {
    static size_t count;

  public:
    Counter() { ++count; }

    inline static size_t totalNumberOfObjects() { return count; }
    inline static size_t totalSize() { return size; }

  protected:
    static size_t size;
    ~Counter() { --count; }
};
size_t Counter::count(0);
size_t Counter::size(0);

}

template<typename T>
class Counter : public total::Counter {
    static size_t count;
    static size_t size;

  public:
    Counter()
    {
        ++count;
        total::Counter::size += sizeof(static_cast<const T&>(*this));
    }

    Counter(const Counter&) : Counter() {}
    inline static size_t numberOfObjects() { return count; }

  protected:
    ~Counter()
    {
        --count;
        total::Counter::size -= sizeof(static_cast<const T&>(*this));
    }
};
template<typename T> size_t Counter<T>::count(0);
template<typename T> size_t Counter<T>::size(0);


using namespace std;

template<typename T, int N>
struct A : public Counter<A<T,N>> {
    T data[N];
};

template<typename T, typename S>
struct P : public Counter<P<T,S>> {
    T a = T{};
    S b = S{};
    P() = default;
    P(T&& a, S&& b) : a(std::forward<T&&>(a)), b(std::forward<S&&>(b)) {}
};

int main()
{
    using At = A<int,10>;
    using Pt = P<int, double>;
    using APt = A<Pt, 5>;
    At a1, a2;
    At* pa = new At{};

    cout << At::numberOfObjects() << " " << At::totalNumberOfObjects()
        << " " << At::totalSize() << endl;

    Pt p1{1, 5.3};
    Pt p3{p1};

    cout << At::numberOfObjects() << " " << At::totalNumberOfObjects()
        << " " << At::totalSize() << endl;
    cout << Pt::numberOfObjects() << " " << Pt::totalNumberOfObjects()
        << " " << Pt::totalSize() << endl;

    delete pa;
    cout << At::numberOfObjects() << " " << At::totalNumberOfObjects()
        << " " << At::totalSize() << endl;

    // Here total size counts elements of A::data twice.
    APt ap;
    cout << Pt::numberOfObjects() << " " << Pt::totalNumberOfObjects()
        << " " << Pt::totalSize() << endl;
    cout << APt::numberOfObjects() << " " << APt::totalNumberOfObjects()
        << " " << APt::totalSize() << endl;

    return 0;
}

/** Expected output (can depend on compiler)
  3 3 120
  3 5 152
  2 5 152
  2 4 112
  7 10 280
  1 10 280
  */

// vim: fen
