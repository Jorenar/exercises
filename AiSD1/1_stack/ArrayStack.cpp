#include "ArrayStack.hpp"

#include <iostream>

Stack::Stack(const std::size_t N) :
    tmpl::Stack<int,1>::Stack(N)
{
    data = new int[N];
}

Stack::~Stack()
{
    delete [] data;
}
