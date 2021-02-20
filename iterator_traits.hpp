#ifndef ITERATOR_TRAITS_HPP
# define ITERATOR_TRAITS_HPP

namespace ft {

template <typename T>
struct iterator_traits
{
    typedef std::random_access_iterator_tag iterator_category;
    typedef T                               value_type;
    typedef T*                              pointer;
    typedef T&                              reference;
    typedef std::ptrdiff_t                  difference_type;
};


}

#endif