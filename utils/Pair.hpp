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

    Pair() : first(), second() {};

    Pair&   operator=(const Pair& x) {
        first = x.first;
        second = x.second;
    
        return (*this);
    }

    template<class U, class V>
    Pair (const Pair<U, V>& pr) : first(pr.first), second(pr.second) {
    }

    Pair (const first_type& a, const second_type& b) : first(a), second(b) {
    }

    ~Pair() {
        first.~first_type();
        second.~second_type();
    }
};
template<typename T1, typename T2>
std::ostream&   operator<<(std::ostream& out, const Pair<T1, T2>& x) {
    return (out << x.first << ":" << x.second);
}

template <class T1, class T2>
ft::Pair<T1, T2>    make_pair(T1 first, T2 second) {
    return ft::Pair<T1, T2>(first, second);
}

} // ft namespace

#endif
