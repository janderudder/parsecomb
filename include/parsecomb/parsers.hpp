#pragma once
#include "parsecomb/Parser.hpp"



template <typename T>
Parser<T> const Some;


template <typename T>
Parser<T> const No;


template <typename T>
Parser<T> const Any;



#include "parsecomb/priv/parsers.impl.hpp"
