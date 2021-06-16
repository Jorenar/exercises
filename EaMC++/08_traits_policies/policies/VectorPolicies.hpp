#pragma once

#include <cstddef>

class InitPolicy {
  public:
    template<typename T>
        static void init(T d[], size_t N)
        {
            for (int i = 0; i < N; ++i) {
                d[i] = 0;
            }
        }
};

class SafePolicy : public InitPolicy {
    class VectorIndexException : public std::runtime_error {
      public:
        VectorIndexException(const char*  msg) : runtime_error(msg) {}
        VectorIndexException(std::string& msg) : runtime_error(msg) {}
    };

  public:
    static void checkIndex(size_t n, size_t N)
    {
        if (n >= N) {
            throw VectorIndexException("Index out of bounds!");
        }
    }
};

class FastPolicy {
  public:
    template<typename T> static void init(T [], size_t) {}
    static void checkIndex(size_t, size_t) {}
};

class InitFastPolicy : public InitPolicy, public FastPolicy {
  public:
    using InitPolicy::init;
};
