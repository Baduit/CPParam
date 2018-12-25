#pragma once

#include <type_traits>
#include <cstdint>

template <typename T>
using Param = typename std::conditional<std::is_trivially_copyable<T>{} && sizeof(T) <= sizeof(intptr_t), T, const T&>::type;