#ifndef PAIR_HPP
# define PAIR_HPP

#include <iostream>

namespace ft {
    
template <typename T1, typename T2>
class Pair {
public:
    typedef T1  first_type;
    typedef T2  second_type;

    first_type first;
    second_type second;

    Pair() {};

    Pair&   operator=(const Pair& x) {
        first = x.first;
        second = x.second;
    
        return (*this);
    }

    Pair (const Pair& pr) : first(pr.first), second(pr.second) {
    }

    Pair (const first_type& a, const second_type& b) : first(a), second(b) {
    }
};
template<typename T1, typename T2>
std::ostream&   operator<<(std::ostream& out, const Pair<T1, T2>& x) {
    return (out << x.first << ":" << x.second);
}

template <typename T1, typename T2>
Pair<T1, T2>    make_pair(T1 first, T2 second) {
    return Pair<T1, T2>(first, second);
}

} // ft namespace

#endif