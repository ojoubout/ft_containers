#ifndef VECTOR_ITERATOR_HPP
# define VECTOR_ITERATOR_HPP

#include "../iterator_traits.hpp"

namespace ft {

template <typename T>
class vector_iterator : public ft::iterator<std::random_access_iterator_tag, T> {
public:    

    typedef typename ft::iterator<std::random_access_iterator_tag, T>::iterator_category  iterator_category;
    typedef typename ft::iterator<std::random_access_iterator_tag, T>::value_type         value_type;
    typedef typename ft::iterator<std::random_access_iterator_tag, T>::pointer            pointer;
    typedef typename ft::iterator<std::random_access_iterator_tag, T>::reference          reference;
    typedef typename ft::iterator<std::random_access_iterator_tag, T>::difference_type    difference_type;

    vector_iterator() : _ptr(NULL) {};
    vector_iterator(pointer ptr) : _ptr(ptr) {};
    vector_iterator &operator=(vector_iterator const &other) {
        _ptr = other._ptr;
        return (*this);
    }

    reference   operator*() { return *_ptr; };
    pointer     operator->() { return _ptr; };
    // Prefix increment
    vector_iterator& operator++() { ++_ptr; return *this; }  
    // Postfix increment
    vector_iterator operator++(int) { vector_iterator tmp = *this; ++(*this); return tmp; }
    // Prefix decrement
    vector_iterator& operator--() { --_ptr; return *this; }  
    // Postfix decrement
    vector_iterator operator--(int) { vector_iterator tmp = *this; --(*this); return tmp; }

    bool    operator!=(const vector_iterator & it) { return (_ptr != it._ptr); }
    bool    operator==(const vector_iterator & it) { return (_ptr == it._ptr); }

    size_t   operator-(vector_iterator rhs) {return (_ptr - rhs._ptr);}

    vector_iterator   operator-(int rhs) {return vector_iterator(_ptr - rhs);}
    vector_iterator   operator+(int rhs) {return vector_iterator(_ptr + rhs);}


    operator vector_iterator<const value_type> () const { return vector_iterator<const value_type>(_ptr) ; }
    // operator const_iterator () const { return const_iterator(_ptr) ; }

private:
    pointer _ptr;
};

template <typename T>
class vector_reverse_iterator : public ft::iterator<std::random_access_iterator_tag, T> {
        public:

            typedef typename ft::iterator<std::random_access_iterator_tag, T>::iterator_category  iterator_category;
            typedef typename ft::iterator<std::random_access_iterator_tag, T>::value_type         value_type;
            typedef typename ft::iterator<std::random_access_iterator_tag, T>::pointer            pointer;
            typedef typename ft::iterator<std::random_access_iterator_tag, T>::reference          reference;
            typedef typename ft::iterator<std::random_access_iterator_tag, T>::difference_type    difference_type;

            vector_reverse_iterator(pointer ptr) : _ptr(ptr) {};

            reference   operator*() { return *(_ptr - 1); };
            pointer     operator->() { return (_ptr - 1); };
            // Prefix increment
            vector_reverse_iterator& operator++() { --_ptr; return *this; }  
            // Postfix increment
            vector_reverse_iterator operator++(int) { vector_reverse_iterator tmp = *this; ++(*this); return tmp; }
            // Prefix decrement
            vector_reverse_iterator& operator--() { ++_ptr; return *this; }  
            // Postfix decrement
            vector_reverse_iterator operator--(int) { vector_reverse_iterator tmp = *this; --(*this); return tmp; }

            bool    operator!=(const vector_reverse_iterator & it) { return (_ptr != it._ptr); }
            bool    operator==(const vector_reverse_iterator & it) { return (_ptr == it._ptr); }

            vector_reverse_iterator   operator-(int rhs) {return vector_reverse_iterator(_ptr + rhs);}
            vector_reverse_iterator   operator+(int rhs) {return vector_reverse_iterator(_ptr - rhs);}

            // operator const_reverse_iterator  () const { return const_reverse_iterator (_ptr) ; }
            operator vector_reverse_iterator<const value_type> () const { return vector_reverse_iterator<const value_type>(_ptr) ; }


        private:
            pointer _ptr;
    };
}

#endif