#pragma once

#include <type_traits>

template<typename ... Ts>
using void_t = void;

template<typename T, typename = void>
struct hasValueType : std::false_type {};

template<typename T>
struct hasValueType<T, void_t<typename T::value_type> > : std::true_type {};

template<typename T>
class hasSize {
    typedef char yes[1];
    typedef char no[2];
    template<typename C> static yes& test(decltype(&C::size));
    template<typename C> static no&  test(...);
  public:
    static const bool value = sizeof (test<T>(0)) == sizeof (yes);
};


#if __cpp_inline_variables >= 201606L
    #define INLINE inline
#else
    #define INLINE
#endif

template<typename T>
INLINE constexpr bool hasSize_v = hasSize<T>::value;

template<typename T>
INLINE constexpr bool hasValueType_v = hasValueType<T>::value;
