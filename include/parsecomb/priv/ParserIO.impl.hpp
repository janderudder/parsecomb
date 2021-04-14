#include "parsecomb/ParserIO.hpp"



////////////////////////////////////////////////////////////////////////////////
template <typename T>
constexpr ParserIO<T>::ParserIO() noexcept:
    m_begin  {nullptr},
    m_end    {nullptr},
    m_status {Status::Fail}
{
}



template <typename T>
constexpr ParserIO<T>::ParserIO(pointer beg, pointer end) noexcept:
    ParserIO {Status::Fail, beg, end}
{
}



template <typename T>
constexpr ParserIO<T>::ParserIO(reference token) noexcept:
    ParserIO {Status::Fail, &token, (&token)+1}
{
}



template <typename T>
template <typename It, typename /* is_iterator_v<It> */>
constexpr ParserIO<T>::ParserIO(It beg, It end) noexcept:
    ParserIO {Status::Fail, beg.operator->(), end.operator->()}
{
}




template <typename T>
template <size_t array_size>
constexpr ParserIO<T>::ParserIO(T const(&arr)[array_size]) noexcept:
    ParserIO {Status::Fail, arr, arr+array_size}
{
}



template <typename T>
template <typename Ctnr>
constexpr ParserIO<T>::ParserIO(Ctnr const& container) noexcept:
    ParserIO {container.begin(), container.end()}
{
}



// private ctor
template <typename T>
constexpr ParserIO<T>::ParserIO(
    Status status, pointer beg, pointer end
) noexcept:
    m_begin  {beg},
    m_end    {end},
    m_status {status}
{
}



////////////////////////////////////////////////////////////////////////////////
template <typename T>
constexpr auto ParserIO<T>::succeed(size_t consume) const -> ParserIO
{
    return {Status::Success, m_begin+consume, m_end};
}



template <typename T>
constexpr auto ParserIO<T>::fail() const -> ParserIO
{
    return {Status::Fail, m_begin, m_end};
}



////////////////////////////////////////////////////////////////////////////////
template <typename T>
constexpr auto ParserIO<T>::size() const -> size_t
{
    return m_end - m_begin;
}



template <typename T>
constexpr auto ParserIO<T>::is_empty() const -> bool
{
    return 0 == size();
}



template <typename T>
constexpr auto ParserIO<T>::is_success() const -> bool
{
    return m_status == Status::Success;
}



////////////////////////////////////////////////////////////////////////////////
template <typename T>
constexpr auto ParserIO<T>::operator[](size_t index) const noexcept -> reference
{
    return *(m_begin+index);
}



////////////////////////////////////////////////////////////////////////////////
template <typename T>
constexpr auto ParserIO<T>::begin() const -> iterator
{
    return m_begin;
}



template <typename T>
constexpr auto ParserIO<T>::end() const -> iterator
{
    return m_end;
}



template <typename T>
constexpr auto ParserIO<T>::cbegin() const -> iterator
{
    return m_begin;
}



template <typename T>
constexpr auto ParserIO<T>::cend() const -> iterator
{
    return m_end;
}
