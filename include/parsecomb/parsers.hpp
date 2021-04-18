#pragma once
#include "parsecomb/Parser.hpp"



template <typename T>
Parser<T> const Some;


template <typename T>
Parser<T> const Any;


template <typename T>
Parser<T> const EmptyInput;



#include "parsecomb/priv/parsers.impl.hpp"
