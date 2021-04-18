#include "parsecomb/parsers.hpp"
#include "parsecomb/combinators.hpp"



template <typename T>
Parser<T> const Some = [](ParserIO<T> const& input) -> ParserIO<T>
{
    return (!input.is_empty()) ? input.succeed(1) : input.fail();
};



template <typename T>
Parser<T> const Any = [](ParserIO<T> const& input) -> ParserIO<T>
{
    return (!input.is_empty()) ? input.succeed(1) : input.succeed(0);
};



template <typename T>
Parser<T> const EmptyInput = [](ParserIO<T> const& input) -> ParserIO<T>
{
    return (input.is_empty()) ? input.succeed(0) : input.fail();
};
