#include "parsecomb/parsecomb.hpp"
#include "parsecomb/variadic-combinators.hpp"
#include "parsecomb/test_parser.hpp"
#include <string>
#include <string_view>
#include <vector>



using Token = std::string;



void variadic_combinators_sample()
{
    auto const _a = TokenParser<Token>("a");
    auto const _b = TokenParser<Token>("b");
    auto const _c = TokenParser<Token>("c");


    // variadic combination
    auto const a_b_c = FirstMatch(_a, _b, _c);


    // variadic combination
    auto const three_times_a_or_b_or_c = Sequence<Token>(a_b_c, a_b_c, a_b_c);


    // inputs
    Token const abc[3]   =  {"a", "b", "c"};
    Token const aac[3]   =  {"a", "a", "c"};
    Token const acb[3]   =  {"a", "c", "b"};
    Token const abcd[4]  =  {"a", "b", "c", "d"};
    Token const cbaz[4]  =  {"c", "b", "a", "z"};
    Token const adca[4]  =  {"a", "d", "c", "a"};
    Token const a[1]     =  {"a"};
    Token const ab[2]    =  {"a", "b"};

    test_parserw(32, three_times_a_or_b_or_c, abc);
    test_parserw(32, three_times_a_or_b_or_c, aac);
    test_parserw(32, three_times_a_or_b_or_c, acb);
    test_parserw(32, three_times_a_or_b_or_c, abcd);
    test_parserw(32, three_times_a_or_b_or_c, cbaz);
    test_parserw(32, three_times_a_or_b_or_c, adca);
    test_parserw(32, three_times_a_or_b_or_c, a);
    test_parserw(32, three_times_a_or_b_or_c, ab);
}
