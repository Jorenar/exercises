#ifndef PRIORITYQUEUE_HPP_
#  error Template implementation file should only be included from corresponding header file
#endif // PRIORITYQUEUE_HPP_

#include <stdexcept>
#include <utility>

#define IPP_TPL template<typename T>

#include <algorithm>
#include <utility>

IPP_TPL PriorityQueue<T>::PriorityQueue() :
    heap(16), count{0}
{}

IPP_TPL PriorityQueue<T>::~PriorityQueue()
{
    delete [] heap.data;
}

IPP_TPL PriorityQueue<T>::Heap::Heap(std::size_t n) :
    data{ new QueueElem<T>[n] }, minCap{ n }, capacity{ n }
{}


IPP_TPL void PriorityQueue<T>::insert(T x, int k)
{
    if (count >= heap.capacity) {
        heap.enlarge(2);
    }

    heap[count] = { k, x };
    ++count;

    std::size_t i = count - 1;
    while (i != 0 && heap[heap.parent(i)] < heap[i]) {
        std::swap(heap[heap.parent(i)], heap[i]);
        i = heap.parent(i);
    }
}

IPP_TPL QueueElem<T> PriorityQueue<T>::max() const
{
    if (count == 0) {
        throw std::out_of_range{"Queue is empty!"};
    }
    return heap[0];
}

IPP_TPL QueueElem<T> PriorityQueue<T>::extractMax()
{
    if (count == 0) {
        throw std::out_of_range{"Queue is empty!"};
    }

    auto temp = heap[0];

    heap[0] = heap[count-1];
    --count;

    heapify(0);

    if (count > heap.minCap && count <= heap.capacity / 3) {
        heap.enlarge(0.5);
    }

    return temp;
}

IPP_TPL void PriorityQueue<T>::heapify(std::size_t i)
{
    auto largest = i;

    auto left = heap.leftChild(i);
    if (left <= count && heap[left] > heap[largest]) {
        largest = left;
    }

    auto right = heap.rightChild(i);
    if (right <= count && heap[right] > heap[largest]) {
        largest = right;
    }

    if (largest != i) {
        std::swap(heap[i], heap[largest]);
        heapify(largest);
    }
}

IPP_TPL void PriorityQueue<T>::Heap::enlarge(float factor)
{
    if (factor <= 0) {
        throw std::invalid_argument{ "You cannot resize to zero!" };
    }

    std::size_t newCapacity = capacity * factor;
    if (newCapacity == 0) {
        throw std::runtime_error{ "New capacity cannot be zero!\n"
                                  "\tcapacity = " + std::to_string(capacity) + "\n"
                                  "\tfactor   = " + std::to_string(factor) };
    }

    auto newData = new QueueElem<T>[newCapacity];

    std::copy_n(data, std::min(capacity, newCapacity), newData);
    delete[] data;

    data = newData;
    capacity = newCapacity;
}

#undef IPP_TPL
