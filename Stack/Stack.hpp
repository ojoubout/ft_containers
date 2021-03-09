#ifndef STACK_HPP
# define STACK_HPP

#include "../Deque/Deque.hpp"

namespace ft {

template <class T, class Container = Deque<T> >
class Stack {
public:
    typedef T           value_type;
    typedef Container   container_type;
    typedef size_t      size_type;

    explicit Stack (const container_type& ctnr = container_type()) : _container(ctnr) {};

    bool empty() const {
        return _container.empty();
    }

    size_type size() const {
        return _container.size();
    }

    value_type& top() {
        return _container.back();
    }
    const value_type& top() const {
        return _container.back();
    }

    void push (const value_type& val) {
        _container.push_back(val);
    }

    void pop() {
        _container.pop_back();
    }

    template <class T1, class Container1>
    friend bool operator== (const Stack<T1,Container1>& lhs, const Stack<T1,Container1>& rhs);
    template <class T1, class Container1>
    friend bool operator!= (const Stack<T1,Container1>& lhs, const Stack<T1,Container1>& rhs);
    template <class T1, class Container1>
    friend bool operator<  (const Stack<T1,Container1>& lhs, const Stack<T1,Container1>& rhs);
    template <class T1, class Container1>
    friend bool operator<= (const Stack<T1,Container1>& lhs, const Stack<T1,Container1>& rhs);
    template <class T1, class Container1>
    friend bool operator>  (const Stack<T1,Container1>& lhs, const Stack<T1,Container1>& rhs);
    template <class T1, class Container1>
    friend bool operator>= (const Stack<T1,Container1>& lhs, const Stack<T1,Container1>& rhs);

protected:
    container_type  _container;
};

template <class T, class Container>
bool operator== (const Stack<T,Container>& lhs, const Stack<T,Container>& rhs) {
    return (lhs._container == rhs._container);
}

template <class T, class Container>
bool operator!= (const Stack<T,Container>& lhs, const Stack<T,Container>& rhs) {
    return (lhs._container != rhs._container);
}

template <class T, class Container>
bool operator<  (const Stack<T,Container>& lhs, const Stack<T,Container>& rhs) {
    return (lhs._container < rhs._container);
}

template <class T, class Container>
bool operator<= (const Stack<T,Container>& lhs, const Stack<T,Container>& rhs) {
    return (lhs._container <= rhs._container);
}

template <class T, class Container>
bool operator>  (const Stack<T,Container>& lhs, const Stack<T,Container>& rhs) {
    return (lhs._container > rhs._container);
}

template <class T, class Container>
bool operator>= (const Stack<T,Container>& lhs, const Stack<T,Container>& rhs) {
    return (lhs._container >= rhs._container);
}

} // ft namespace

#endif
