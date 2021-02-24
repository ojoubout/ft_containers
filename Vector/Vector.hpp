#ifndef VECTOR_HPP
# define VECTOR_HPP

#include <limits>
#include <cstddef>
#include "../iterator_traits.hpp"
#include <cmath>
#include <cstring>

namespace ft {

template <typename T>
class Vector {
public:
    typedef T           value_type;
    typedef T&          reference;
    typedef const T&    const_reference;
    typedef T*          pointer;
    typedef const T*    const_pointer;
    typedef ptrdiff_t   difference_type;
    typedef size_t      size_type;

    
    struct const_iterator : public iterator_traits<T> {
        public:    
            const_iterator() : _ptr(NULL) {};
            const_iterator(pointer ptr) : _ptr(ptr) {};
            const_iterator &operator=(const_iterator const &other) {
                _ptr = other._ptr;
                return (*this);
            }


            reference   operator*() { return *_ptr; };
            pointer     operator->() { return _ptr; };
            // Prefix increment
            const_iterator& operator++() { ++_ptr; return *this; }  
            // Postfix increment
            const_iterator operator++(int) { const_iterator tmp = *this; ++(*this); return tmp; }
            // Prefix decrement
            const_iterator& operator--() { --_ptr; return *this; }  
            // Postfix decrement
            const_iterator operator--(int) { const_iterator tmp = *this; --(*this); return tmp; }

            size_type   operator-(const_iterator rhs) {return (_ptr - rhs._ptr);}


            bool    operator!=(const_iterator & it) { return (_ptr != it._ptr); }
            bool    operator==(const_iterator & it) { return (_ptr == it._ptr); }


        protected:
            pointer _ptr;
    };
    struct iterator : public iterator_traits<T> {
        public:    
            iterator() : _ptr(NULL) {};
            iterator(pointer ptr) : _ptr(ptr) {};
            iterator &operator=(iterator const &other) {
                _ptr = other._ptr;
                return (*this);
            }

            reference   operator*() { return *_ptr; };
            pointer     operator->() { return _ptr; };
            // Prefix increment
            iterator& operator++() { ++_ptr; return *this; }  
            // Postfix increment
            iterator operator++(int) { iterator tmp = *this; ++(*this); return tmp; }
            // Prefix decrement
            iterator& operator--() { --_ptr; return *this; }  
            // Postfix decrement
            iterator operator--(int) { iterator tmp = *this; --(*this); return tmp; }

            bool    operator!=(iterator const & it) { return (_ptr != it._ptr); }
            bool    operator==(iterator const & it) { return (_ptr == it._ptr); }
            size_type   operator-(iterator rhs) {return (_ptr - rhs._ptr);}

            operator const_iterator () const { return const_iterator(_ptr) ; }

        protected:
            pointer _ptr;
    };

    struct const_reverse_iterator : public iterator_traits<T> {
        public:    
            const_reverse_iterator (pointer ptr) : _ptr(ptr) {};

            reference   operator*() { return *(_ptr - 1); };
            pointer     operator->() { return (_ptr - 1); };
            // Prefix increment
            const_reverse_iterator & operator++() { --_ptr; return *this; }  
            // Postfix increment
            const_reverse_iterator  operator++(int) { const_reverse_iterator  tmp = *this; ++(*this); return tmp; }
            // Prefix decrement
            const_reverse_iterator & operator--() { ++_ptr; return *this; }  
            // Postfix decrement
            const_reverse_iterator  operator--(int) { const_reverse_iterator  tmp = *this; --(*this); return tmp; }

            bool    operator!=(const_reverse_iterator & it) { return (_ptr != it._ptr); }
            bool    operator==(const_reverse_iterator & it) { return (_ptr == it._ptr); }


        private:
            pointer _ptr;
    };

    struct reverse_iterator : public iterator_traits<T> {
        public:
            reverse_iterator(pointer ptr) : _ptr(ptr) {};

            reference   operator*() { return *(_ptr - 1); };
            pointer     operator->() { return (_ptr - 1); };
            // Prefix increment
            reverse_iterator& operator++() { --_ptr; return *this; }  
            // Postfix increment
            reverse_iterator operator++(int) { reverse_iterator tmp = *this; ++(*this); return tmp; }
            // Prefix decrement
            reverse_iterator& operator--() { ++_ptr; return *this; }  
            // Postfix decrement
            reverse_iterator operator--(int) { reverse_iterator tmp = *this; --(*this); return tmp; }

            operator const_reverse_iterator  () const { return const_reverse_iterator (_ptr) ; }

            bool    operator!=(reverse_iterator & it) { return (_ptr != it._ptr); }
            bool    operator==(reverse_iterator & it) { return (_ptr == it._ptr); }


        private:
            pointer _ptr;
    };

    explicit Vector () {
        init();
    }

    explicit Vector (size_type n, const value_type& val = value_type()) {
        init();
        insert(begin(), n, val);
    }

    Vector (iterator first, iterator last) {
        init();
        insert(begin(), first, last);
    }
    Vector (const Vector& x) {
        init();
        *this = x;
    }

    ~Vector() {
        clear();
        ::operator delete(_container);
    }

    Vector& operator= (const Vector& x) {
        // clear();
        assign(x.begin(), x.end());
        return (*this);
    }
    // Iterators:

    const_iterator begin() const {
        return (const_iterator(_container));
    }
    iterator begin() {
        return (iterator(_container));
    }
    const_iterator end() const {
        return (const_iterator(_container + _size));
    }
    iterator end() {
        return (iterator(_container + _size));
    }
    const_reverse_iterator rbegin() const {
        return (const_reverse_iterator(_container + _size));
    }
    const_reverse_iterator rend() const {
        return (const_reverse_iterator(_container));
    }
    reverse_iterator rbegin() {
        return (reverse_iterator(_container + _size));
    }
    reverse_iterator rend() {
        return (reverse_iterator(_container));
    }

    // Capacity:

    size_type size() const {
        return _size;
    }

    size_type max_size() const {
        return (std::numeric_limits<difference_type>::max());
    }

    void resize (size_type n, value_type val = value_type()) {
        if (n <= _size) {
            _size = n;
        } else {
            insert(end(), n - _size, val);
        }
    }

    size_type capacity() const {
        return _capacity;
    }

    bool empty() const {
        return (_size == 0);
    }

    void reserve (size_type n) {
        if (n > _capacity) {
            _capacity = n;
            pointer new_container = static_cast<pointer>(::operator new(sizeof(value_type) * n));
            std::memcpy(new_container, _container, _size * sizeof(value_type));
            size_type size = _size;
            clear();
            _size = size;
            ::operator delete(_container);
            _container = new_container;   
        }
    }

    // Element access:

    reference operator[] (size_type n) {
        return _container[n];   
    }
    const_reference operator[] (size_type n) const {
        return _container[n];
    }
    //--//
    reference at (size_type n) {
        if (n >= _size) {
            throw std::out_of_range("ft::Vector::at");
        }
        return _container[n];
    }
    const_reference at (size_type n) const {
        if (n >= _size) {
            throw std::out_of_range("ft::Vector::at");
        }
        return _container[n];
    }
    //--//
    reference front() {
        return _container[0];
    }
    const_reference front() const {
        return _container[0];
    }
    //--//
    reference back() {
        return _container[_size - 1];
    }
    const_reference back() const {
        return _container[_size - 1];
    }

    // Modifiers:

    void assign (const_iterator first, const_iterator last) {
        size_type n = last - first;
        if (n > _capacity) {
            reserve(n);
        }
        int i = 0;
        for (const_iterator it = first; it != last; ++it) {
            _container[i] = *it;
            i++;
        }
        _size = i;
    }
    void assign (size_type n, const value_type& val) {
        if (n > _capacity) {
            reserve(n);
        }
        for (size_type i = 0; i < n; ++i) {
            _container[i] = val;
        }
        _size = n;
    }
    //--//
    void push_back (const value_type& val) {
        insert(end(), val);
    }
    //--//
    void pop_back() {
        erase(end());
    }

    //--//
    iterator insert (iterator position, const value_type& val) {
        size_type pos = position - begin();
        insert(position, 1, val);
        return (iterator(_container + pos));

    }
    void insert (iterator position, size_type n, const value_type& val) {
        size_type   pos = position - begin();
        if (_size + n > _capacity) {
            int r = ((_size + n) ^ ((_size + n) % 2)) << 1;
            if (_size + n == 1)
                r = 1;    
            else if ((_size + n) % 2 == 0)
                r = _size + n;
            reserve(r);
        }
        std::memcpy(&_container[pos + n], &_container[pos], (_size - pos) * sizeof(value_type));
        for (size_type i = pos; i < pos + n; ++i) {
            _container[i] = val;
        }
        _size += n;
    }
    void insert (iterator position, const_iterator first, const_iterator last) {
        for (const_iterator it = first; it != last; ++it) {
            position = insert(position, *it);
            position++;
        }
    }
    //--//
    iterator erase (iterator position) {
        size_type pos = position - begin();
        if (position != end()) {
            std::memcpy(_container + pos, _container + pos + 1, (_size - pos) * sizeof(value_type));
        }
        _size--;
        return (position);
    }
    iterator erase (iterator first, iterator last) {
        size_type pos = first - begin();
        size_type len = last - first;
        std::memcpy(_container + pos, _container + pos + len, (_size - len) * sizeof(value_type));
        _size -= len;
        return (first);
    }
    //--//
    void swap (Vector& x) {
        pointer container = x._container;
        size_type capacity = x._capacity;
        size_type size = x._size;

        x._container = _container;
        x._capacity = _capacity;
        x._size = _size;
        _container = container;
        _capacity = capacity;
        _size = size;
    }
    //--//
    void clear() {
        for (size_type i = 0; i < _size; ++i) {
            _container[i].value_type::~value_type();
        }
        _size = 0;
    }
    //--//

    // Utils

    void print_list() {
        const_iterator it = begin();
        const_iterator ite = end();
        while (it != ite) {
            std::cout << "value: " << *it << " ";
            it++;
        }
        std::cout << std::endl;
    }
private:
    pointer     _container;
    size_type   _capacity;
    size_type   _size;
    void    init() {
        _container = static_cast<pointer>(::operator new(0));;
        _size = 0;
        _capacity = 0;
    }
};

template <class T>
bool operator== (const Vector<T>& lhs, const Vector<T>& rhs) {
    if (lhs.size() != rhs.size()) {
        return (false);
    }
    typename Vector<T>::const_iterator lhs_it = lhs.begin();
    typename Vector<T>::const_iterator lhs_ite = lhs.end();
    typename Vector<T>::const_iterator rhs_it = rhs.begin();

    if (lhs.size() != rhs.size())
        return (false);
    while (lhs_it != lhs_ite) {
        if (*lhs_it++ != *rhs_it++)
            return (false);
    }
    return (true);
}

template <class T>
bool operator!= (const Vector<T>& lhs, const Vector<T>& rhs) {
    return !(lhs == rhs);
}

template <class T>
bool operator<  (const Vector<T>& lhs, const Vector<T>& rhs) {
    typename Vector<T>::const_iterator lhs_it = lhs.begin();
    typename Vector<T>::const_iterator lhs_ite = lhs.end();
    typename Vector<T>::const_iterator rhs_it = rhs.begin();
    typename Vector<T>::const_iterator rhs_ite = rhs.end();
    while (lhs_it != lhs_ite && rhs_it != rhs_ite) {
        if (*lhs_it < *rhs_it)
            return (true);
        else if (*lhs_it > *rhs_it)
            return (false);
        lhs_it++;
        rhs_it++;
    }
    if (lhs_it == lhs_ite && rhs_it != rhs_ite)
        return (true);
    return (false);
}

template <class T>
bool operator<= (const Vector<T>& lhs, const Vector<T>& rhs) {
    return !(lhs > rhs);
}

template <class T>
bool operator>  (const Vector<T>& lhs, const Vector<T>& rhs) {
    return (rhs < lhs);
}

template <class T>
bool operator>= (const Vector<T>& lhs, const Vector<T>& rhs) {
    return !(lhs < rhs);
}

template<typename T>
void swap(Vector<T> &first, Vector<T> &second) {
	first.swap(second);
}

} // ft namespace 

#endif