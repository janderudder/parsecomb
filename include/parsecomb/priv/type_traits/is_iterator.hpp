#pragma once
#include <iterator>
#include <type_traits>



template <typename T, typename>
struct is_iterator;


template <typename T>
struct is_iterator_or_pointer;



////////////////////////////////////////////////////////////////////////////////
template <typename T, typename = void>
struct is_iterator
    : std::false_type {};



template <typename T>
struct is_iterator<T, std::void_t<typename std::iterator_traits<T>::value_type>>
    : std::true_type {};



template <typename T>
constexpr bool is_iterator_v = is_iterator<T>::value;



////////////////////////////////////////////////////////////////////////////////
template <typename T>
struct is_iterator_or_pointer
{
    constexpr static bool value = is_iterator_v<T> || std::is_pointer_v<T>;
};



template <typename T>
constexpr bool is_iterator_or_pointer_v = is_iterator_or_pointer<T>::value;
