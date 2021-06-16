#pragma once

#include <stack>

template<std::size_t N>
class Ex_1_28 {
    bool data[N];
    std::stack<std::size_t> helper;

public:

    std::size_t select()
    {
        if (!helper.empty()) {
            std::size_t i = helper.pop();
            data[i] = false;
            return i;
        }
    }

    void insert(std::size_t i)
    {
        if (! data[i]) {
            data[i] = true;
            helper.push(i);
        }
    }

    bool search(std::size i) { return data[i]; }

}
