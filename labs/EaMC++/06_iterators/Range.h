#pragma once

template<typename T>
class Range {
  public:
    Range(T start_, T stop_, T step_) : start(start_), stop(stop_), step(step_), current(start) {}
    Range(T start_, T stop_) : start(start_), stop(stop_), step(1), current(start) {}
    Range(T stop_) : start(0), stop(stop_), step(1), current(start) {}

    class Iterator {
      public:

        Iterator(const T s_) : c(current), s(s_) {}

        Iterator(const T c_, const T s_) : c(c_), s(s_) {}

        Iterator& operator=(T x)
        {
            c = x;
            return *this;
        }

        Iterator& operator ++()
        {
            c += s;
            return *this;
        }

        Iterator operator ++(int)
        {
            Iterator temp = *this;
            ++(*this);
            return temp;
        }

        bool operator !=(const Iterator& obj)
        {
            return c < obj.c;
        }

        T operator *()
        {
            return c;
        }

      private:
        T c;
        const T s;
    };

    inline Iterator begin() { return Iterator(start, step); }
    inline Iterator end() { return Iterator(stop, step); }

  private:
    T start;
    T stop;
    T step;
    T current;
};

template<typename T, typename... A>
Range<T> make_range(T x, A... args)
{
    return Range<T>(x, args...);
}

// vim: ft=cpp fen fdl=2
