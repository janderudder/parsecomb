#pragma once
#include "parsecomb/priv/type_traits/is_iterator.hpp"
#include <cstddef>
#include <iterator>
#include <type_traits>



template <typename T>
class ParserIO
{
public:
    using token_type    = std::remove_cv_t<std::remove_reference_t<T>>;
    using pointer       = token_type const*;
    using reference     = token_type const&;
    using iterator      = pointer;

private:
    pointer                     m_begin,
                                m_end;
    enum Status {Fail,Success}  m_status;

public:
    constexpr ParserIO() noexcept;
    constexpr ParserIO(pointer, pointer) noexcept;
    constexpr ParserIO(reference) noexcept;

    template <typename It, typename=std::enable_if_t<is_iterator_v<It>>>
    constexpr ParserIO(It, It) noexcept;

    template <typename Ctnr>
    constexpr ParserIO(Ctnr const&) noexcept;

    constexpr auto succeed(size_t) const -> ParserIO;
    constexpr auto fail()          const -> ParserIO;

    constexpr auto size()          const -> size_t;
    constexpr auto is_empty()      const -> bool;
    constexpr auto is_success()    const -> bool;

    constexpr auto operator[](size_t) const noexcept -> reference;

    constexpr auto begin()  const -> iterator;
    constexpr auto end()    const -> iterator;
    constexpr auto cbegin() const -> iterator;
    constexpr auto cend()   const -> iterator;

private:
    // private constructor, called by most other constructors.
    constexpr ParserIO(Status, pointer, pointer) noexcept;

};



#include "parsecomb/priv/ParserIO.impl.hpp"
