#include "parsecomb/variadic-combinators.hpp"



namespace parsecomb_private
{


template <typename T, typename... Ps>
constexpr auto variadic_call(
    CombinatorBinary<T> const& c, Parser<T> const& p, Ps const&... ps
) -> Parser<T>
{
    if constexpr (sizeof...(ps) == 1) {
        return c(p, ps...);
    }
    else {
        return c(p, variadic_call<T>(c, ps...));
    }
}


template <typename T>
using ComBinPtr = Parser<T>(*)(Parser<T> const&,Parser<T>const&);



} // parsecomb_private::




////////////////////////////////////////////////////////////////////////////////
template <typename T, typename... Ps>
constexpr auto Sequence(Parser<T> const& p, Ps const&... ps) -> Parser<T>
{
    constexpr parsecomb_private::ComBinPtr<T> combinator {Sequence};
    return parsecomb_private::variadic_call<T>(combinator, p, ps...);
}



template <typename T, typename... Ps>
constexpr auto FirstMatch(Parser<T> const& p, Ps const&... ps) -> Parser<T>
{
    constexpr parsecomb_private::ComBinPtr<T> combinator {FirstMatch};
    return parsecomb_private::variadic_call<T>(combinator, p, ps...);
}



template <typename T, typename... Ps>
constexpr auto BestMatch(Parser<T> const& p, Ps const&... ps) -> Parser<T>
{
    constexpr parsecomb_private::ComBinPtr<T> combinator {BestMatch};
    return parsecomb_private::variadic_call<T>(combinator, p, ps...);
}
