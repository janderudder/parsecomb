/*


Demonstrate use of the function `ConvertParser`

to build a `Parser<Token>` from a combination of several `Parser<char>`.


*/
#include "parsecomb/parsecomb.hpp"
#include "parsecomb/test_parser.hpp"
#include <iostream>
#include <string>
#include <string_view>
#include <vector>


// A token may contain other information beside its value, for instance its
// position in the source input. But here we'll just have string value.
struct Token
{
    std::string value;

    Token(const char* val): value {val} {}
};


// This program will work with two different Parser types :
// Parser<Token> and Parser<char>.
// char is another type of token too, because we can treat the value of 'Token',
// which is a string, as a collection of char.
// So Parser<char> works on an input that is none other than a Token.
void parser_conversion_sample()
{
    // We define some primitive ranges, building blocks.
    Parser<char> const _     = TokenParser<char>('_');
    auto const         alpha = RangeParser<char>('A', 'z');     // A-Z + a-z
    auto const         digit = RangeParser<char>('0', '9');


    // We use combinators to specify what an identifier is allowed to look like.
    // Here, it must begin with an underscore or an alpha character, but then
    // it can have any number of either of those and digits.
    Parser<char> const identifier_char_parser =
        Sequence(
            FirstMatch(alpha, _),
            Optional(OneOrMore(FirstMatch(alpha, FirstMatch(_, digit))))
        );


    // Combinators only work with a single type of parsers, we cannot mix a
    // Parser<char> with a Parser<Token> in a combination.
    // But, it turns out that we can call a Parser<char> with a Token's value
    // as input. So let's convert.
    // We need a way to tell the Parser<char> how to get its input from a Token.
    auto const token_to_input = [](Token const& token) { return token.value; };


    // And we build a Parser<Token> that will internally use a combination of
    // Parser<char> on the char string contained in the available Token.
    Parser<Token> const identifier_parser =
        ConvertParser<Token>(token_to_input, identifier_char_parser);


    // We can now use our object of type Parser<Token> to validate (or not) a
    // token as an identifier.
    test_parser(identifier_parser, Token{"ab_cd"}); // OK
    test_parser(identifier_parser, Token{"_abcd"}); // OK
    test_parser(identifier_parser, Token{"1abcd"}); // NOPE, begins with a digit


    // Just grouping the same previous tokens...
    Token const tokens[3] {"ab_cd", "_abcd", "1abcd"};


    // ...to try and consume as many identifiers we can from the input.
    test_parser(OneOrMore(identifier_parser), tokens); // success: 2, remains: 1


}
