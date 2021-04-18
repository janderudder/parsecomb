#pragma once
#include "parsecomb/combinators.hpp"



template <typename T, typename... Ps>
constexpr auto Sequence(Parser<T> const&, Ps const&...) -> Parser<T>;


template <typename T, typename... Ps>
constexpr auto FirstMatch(Parser<T> const&, Ps const&...) -> Parser<T>;


template <typename T, typename... Ps>
constexpr auto BestMatch(Parser<T> const&, Ps const&...) -> Parser<T>;



#include "parsecomb/priv/variadic-combinators.impl.hpp"
