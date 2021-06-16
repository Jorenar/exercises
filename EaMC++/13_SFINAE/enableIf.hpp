#pragma once

#include <iostream>
#include "checkIfHas.hpp"

namespace v1 {

  template<typename T>
  std::enable_if_t<hasSize_v<T> && hasValueType_v<T>, size_t> getSize(const T& x)
  {
      return x.size() * sizeof (typename T::value_type);
  }

  template<typename T>
  std::enable_if_t<!(hasSize_v<T> && hasValueType_v<T>), size_t> getSize(const T& x)
  {
      return sizeof (x);
  }

}

#if __cpp_if_constexpr >= 201606L

namespace v2 {

  template<typename T>
  size_t getSize(const T& x)
  {
      if constexpr (hasSize_v<T> && hasValueType_v<T>) {
          return x.size() * sizeof (typename T::value_type);
      }
      else {
          return sizeof (x);
      }
  }

}

#else

namespace v2 = v1;

#endif
