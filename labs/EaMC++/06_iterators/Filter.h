#pragma once

// At this point, I've basically copied the code from lecture, but somehow
// I constantly get segmentation fault

#include <type_traits>
#include <utility>

template<typename C, typename P>
class Filter {
  public:
    Filter(C c, P p) : container(c), predicate(p) {}

    class Iterator;
    using iterator = Iterator;

    class Iterator {
      public:
        typename std::decay_t<C>::iterator current;
        using T = decltype(*current);
        Iterator(Filter& f, bool flag = false) :
            filter(f),
            current(flag ? filter.container.end() : filter.container.begin())
        {}

        Iterator& operator ++()
        {
            do {
                current++;
            } while (current != filter.container.end() && filter.predicate(*current));
            return *this;
        }

        Iterator operator ++(int) { Iterator temp(*this); ++(*this); return temp; }

        T& operator *() { return *current; }
        T  operator *() const { return *current; }

        bool operator !=(const Iterator& obj) { return current != obj.current; }
        bool operator ==(const Iterator& obj) { return current == obj.current; }

      private:
        Filter& filter;
    };

    iterator begin() { return iterator(*this); }
    iterator end()   { return iterator(*this, true); }

  private:
    C container;
    P predicate;
};

template<typename C, typename P>
Filter<C,P> make_filter(C&& c, P&& p)
{
    return { std::forward<C&&>(c), std::forward<P&&>(p) };
}

// vim: ft=cpp fen
