#ifndef PRIORITYQUEUE_HPP_
#define PRIORITYQUEUE_HPP_

#include <algorithm>
#include <cstddef>

template<typename T>
struct QueueElem {
    int priority;
    T obj;
};

template<typename T>
bool operator<(const QueueElem<T>& a, const QueueElem<T>& b)
{
    if (a.priority == b.priority) {
        return a.obj < b.obj;
    }
    return a.priority < b.priority;
}

template<typename T>
bool operator>(const QueueElem<T>& a, const QueueElem<T>& b)
{
    return b < a;
}

template<typename T>
class PriorityQueue {
    struct Heap {
        QueueElem<T>* data;
        std::size_t capacity;
        const std::size_t minCap;

        Heap(std::size_t n);

        /* */ QueueElem<T>& operator[](std::size_t i)       { return data[i]; }
        const QueueElem<T>& operator[](std::size_t i) const { return data[i]; }

        static inline std::size_t parent(std::size_t i)     { return (i-1)/2; }
        static inline std::size_t leftChild(std::size_t i)  { return 2*i + 1; }
        static inline std::size_t rightChild(std::size_t i) { return 2*i + 2; }

        void enlarge(float factor);
    };

    Heap heap;
    std::size_t count;

    void heapify(std::size_t i);

public:
    PriorityQueue();
    ~PriorityQueue();

    void insert(T x, int k);    // wstawia obiekt x do kolejki i przypisuje mu priorytet k
    QueueElem<T> max() const;   // zwraca obiekt o największym priorytecie w kolejce nie usuwając go
    QueueElem<T> extractMax();  // usuwa z kolejki i zwraca obiekt o największym priorytecie
};

#include "PriorityQueue.ipp"

#endif // PRIORITYQUEUE_HPP_
