#ifndef PAIR_HPP
# define PAIR_HPP

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

    template<class U, class V>
    Pair (const Pair<U,V>& pr) {
        first = first_type(pr.first);
        second = second_type(pr.second);
    }

    Pair (const first_type& a, const second_type& b) {
        first = first_type(a);
        second = second_type(b);
    }
};

#endif