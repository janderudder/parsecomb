# parsecomb


Studying parser combinators in C++17. Not production ready or anything.



## Sample

```cpp
#include "parsecomb/parsecomb.hpp"
#include "parsecomb/test_parser.hpp"
#include <string>
#include <vector>

using Token = std::string;


// define parsers of type Parser<Token>
auto const hello       = TokenParser<Token>("hello");
auto const world       = TokenParser<Token>("world");
auto const paren_left  = TokenParser<Token>("(");
auto const paren_right = TokenParser<Token>(")");


// define combinators
auto const in_parens   = Between(paren_left, paren_right);
auto const no_parens   = Not(in_parens);


// two sets of input
std::vector<Token> const tokens1 {
    "hello", "world", "!"
};

std::vector<Token> const tokens2 {
    "(", "hello", ")", "(", "world", ")"
};


// Combine the above parsers into sequences.
// Output of test_parser is of format:  [is_success, remaining_count]
test_parser(Sequence(hello, world), tokens1);                       // [true, 1]
test_parser(Sequence(hello, world), tokens2);                       // [false,6]
test_parser(Sequence(in_parens(hello), in_parens(world)), tokens1); // [false,3]
test_parser(Sequence(in_parens(hello), in_parens(world)), tokens2); // [true, 0]
test_parser(Sequence(no_parens(hello), no_parens(world)), tokens1); // [true, 1]
test_parser(Sequence(no_parens(hello), no_parens(world)), tokens2); // [false,6]

// Parse both "hello" and "(hello)"
test_parser(FirstMatch(hello, in_parens(hello)), tokens1);          // [true, 2]
test_parser(FirstMatch(hello, in_parens(hello)), tokens2);          // [true, 3]

// Consume several Tokens, each being between parentheses
test_parser(Several(in_parens(Some<Token>)), tokens1);              // [false,3]
test_parser(Several(in_parens(Some<Token>)), tokens2);              // [true, 0]


```



## Overview


```hs
Parser<T> : ParserIO<T> -> ParserIO<T>
```


- `Parser<T>` is a generic class that works on a contiguous collection of `T`s. It is a callable type, whose call operator takes a `ParserIO`.

- `ParserIO<T>` is the generic type serving as input to and output from `Parser`. It can be constructed directly from a range or container of `T`s, enabling more convenient calls to `Parser` (like `parser(container)`).

- A Combinator takes one or multiple parsers and wraps them in a new parser that represents the combination.

- In other words, a `Parser` may be a simple parser applying a single piece of logic, or it may be any combination thereof.

- In yet other words, a `Parser` object may be written directly by the programmer - often as a building block. But the library offers several primitive parsers, intended to be combined. A combination will produce new objects of type `Parser`, capable of more complicated logic.

- `Parser<T1>` and `Parser<T2>` types do not mix together in a combination. An explicit conversion must be used. The `ConvertParser` function is such a way of constructing a new parser from one of another type.



## Notes

The combinator `OptionalNestedBetween` is a hopefully temporary way of getting around an important limitation of this library: the inability to produce recursive combinations of parsers.

It makes it possible to parse with the same parser things like `(expression)` and `(expression (expression))`.
