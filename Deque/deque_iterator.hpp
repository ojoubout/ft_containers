#ifndef DEQUE_ITERATOR_HPP
# define DEQUE_ITERATOR_HPP

#include "../iterator_traits.hpp"

namespace ft {

#define BUFF_SIZE 16

template < class T > class Deque;

template <typename T>
class deque_iterator : public ft::iterator<std::random_access_iterator_tag, T> {
    public:    
        typedef typename ft::iterator<std::random_access_iterator_tag, T>::iterator_category  iterator_category;
        typedef typename ft::iterator<std::random_access_iterator_tag, T>::value_type         value_type;
        typedef typename ft::iterator<std::random_access_iterator_tag, T>::pointer            pointer;
        typedef typename ft::iterator<std::random_access_iterator_tag, T>::reference          reference;
        typedef typename ft::iterator<std::random_access_iterator_tag, T>::difference_type    difference_type;

        typedef T**             map_pointer;
        typedef size_t          size_type;

        deque_iterator() {};
        deque_iterator(map_pointer map, size_type index = 0) {
            if (map) {
                set_node(map);
                _curr = _first + index;
            }
        };

        deque_iterator &operator=(const deque_iterator &other) {
            set_node(other._node);
            _curr = other._curr;
            return (*this);
        }

        void    set_node(map_pointer map) {
            _node = map;
            _first = *map;
            _last = _first + BUFF_SIZE;
        }


        reference   operator*() { return *_curr; };
        pointer     operator->() { return _curr; };
        // Prefix increment
        deque_iterator& operator++() {
            ++_curr;
            if (_curr == _last) {
                set_node(_node + 1);
                _curr = _first;
            } 
            return *this;
        }
        // Postfix increment
        deque_iterator operator++(int) { deque_iterator tmp = *this; ++(*this); return tmp; }
        // Prefix decrement
        deque_iterator& operator--() {
            if (_curr == _first) {
                set_node(_node - 1);
                _curr = _last;
            }
            --_curr;
            return *this;
        }  
        // Postfix decrement
        deque_iterator operator--(int) { deque_iterator tmp = *this; --(*this); return tmp; }

        bool    operator!=(const deque_iterator & it) { return (_curr != it._curr); }
        bool    operator==(const deque_iterator & it) { return (_curr == it._curr); }

        size_t   operator-(deque_iterator rhs) {
            size_t map_size = (_node - rhs._node) * BUFF_SIZE;
            size_t size = map_size + (_curr - _first) - (rhs._curr - rhs._first);
            return (size);
        }

        deque_iterator   operator+(int rhs) {
            size_t n = rhs + (_curr - _first);
            return deque_iterator(_node + n / BUFF_SIZE, n % BUFF_SIZE);
        }
        deque_iterator   operator-(int rhs) {
            int n = (_curr - _first) - rhs;
            if (n < 0) {
                n = -n;
                size_type   last_chunk_size = ((n % BUFF_SIZE) == 0 && n != 0) ? BUFF_SIZE : n % BUFF_SIZE ;

                size_t map_size = (n + BUFF_SIZE - 1) / BUFF_SIZE;
                // std::cout << "N: " << n << ", MS: " << map_size << ", M: " << n % BUFF_SIZE << std::endl;
                return deque_iterator(_node - map_size, BUFF_SIZE -  last_chunk_size);
            } else {
                return deque_iterator(_node, n);

            }
        }
        
        bool    operator<(const deque_iterator & it) { return (_curr < it._curr); }
        bool    operator>(const deque_iterator & it) { return (_curr > it._curr); }
        bool    operator<=(const deque_iterator & it) { return (_curr <= it._curr); }
        bool    operator>=(const deque_iterator & it) { return (_curr >= it._curr); }

        deque_iterator   operator+=(int rhs) {return (*this = *this + rhs);};
        deque_iterator   operator-=(int rhs) {return (*this = *this - rhs);};

        reference   operator[](int n) { return *(*this + n); };

        operator deque_iterator<const value_type> () const {
            return deque_iterator<const value_type>(const_cast<const value_type **>(_node), _curr - _first) ; }

    private:
        pointer _curr;       
        pointer _first;     // the begin of the chunk
        pointer _last;      // the end of the chunk
        map_pointer _node;
        friend class Deque<T>;

};

template <typename T>
class deque_reverse_iterator : public ft::iterator<std::random_access_iterator_tag, T> {
    public:    

        typedef typename ft::iterator<std::random_access_iterator_tag, T>::iterator_category  iterator_category;
        typedef typename ft::iterator<std::random_access_iterator_tag, T>::value_type         value_type;
        typedef typename ft::iterator<std::random_access_iterator_tag, T>::pointer            pointer;
        typedef typename ft::iterator<std::random_access_iterator_tag, T>::reference          reference;
        typedef typename ft::iterator<std::random_access_iterator_tag, T>::difference_type    difference_type;

        typedef T**             map_pointer;
        typedef size_t          size_type;

        deque_reverse_iterator() {};
        deque_reverse_iterator(map_pointer map, size_type index) {
            set_node(map);
            _curr = _first + index;
        };

        deque_reverse_iterator &operator=(const deque_reverse_iterator &other) {
            set_node(other._node);
            _curr = other._curr;
            return (*this);
        }

        void    set_node(map_pointer map) {
            _node = map;
            _first = *map;
            _last = _first + BUFF_SIZE;
        }


        reference   operator*() { return *(_curr - 1); };
        pointer     operator->() { return (_curr - 1); };
        // Prefix increment
        deque_reverse_iterator& operator++() {
            --_curr;
            if (_curr == _first) {
                set_node(_node - 1);
                _curr = _last;
            }
            return *this;
        }
        // Postfix increment
        deque_reverse_iterator operator++(int) { deque_reverse_iterator tmp = *this; ++(*this); return tmp; }
        // Prefix decrement
        deque_reverse_iterator& operator--() {
            if (_curr == _last) {
                set_node(_node + 1);
                _curr = _first;
            } 
            ++_curr;
            return *this;
        }  
        // Postfix decrement
        deque_reverse_iterator operator--(int) { deque_reverse_iterator tmp = *this; --(*this); return tmp; }

        bool    operator!=(const deque_reverse_iterator & it) { return (_curr != it._curr); }
        bool    operator==(const deque_reverse_iterator & it) { return (_curr == it._curr); }

        size_t   operator-(deque_reverse_iterator rhs) {
            size_t map_size = (_node - rhs._node) * BUFF_SIZE;
            size_t size = map_size + (_curr - _first) - (rhs._curr - rhs._first);
            return (size);
        }

        deque_reverse_iterator   operator-(int rhs) {
            size_t n = rhs + (_curr - _first);
            return deque_reverse_iterator(_node + n / BUFF_SIZE, n % BUFF_SIZE);
        }

        deque_reverse_iterator   operator+(int rhs) {
            int n = (_curr - _first) - rhs;
            if (n < 0) {
                n = -n;
                size_type   last_chunk_size = ((n % BUFF_SIZE) == 0 && n != 0) ? BUFF_SIZE : n % BUFF_SIZE ;

                size_t map_size = (n + BUFF_SIZE - 1) / BUFF_SIZE;
                // std::cout << "N: " << n << ", MS: " << map_size << ", M: " << n % BUFF_SIZE << std::endl;
                return deque_reverse_iterator(_node - map_size, BUFF_SIZE -  last_chunk_size);
            } else {
                return deque_reverse_iterator(_node, n);

            }
        }
        
        bool    operator<(const deque_reverse_iterator & it) { return (_curr < it._curr); }
        bool    operator>(const deque_reverse_iterator & it) { return (_curr > it._curr); }
        bool    operator<=(const deque_reverse_iterator & it) { return (_curr <= it._curr); }
        bool    operator>=(const deque_reverse_iterator & it) { return (_curr >= it._curr); }

        deque_reverse_iterator   operator+=(int rhs) {return (*this = *this + rhs);};
        deque_reverse_iterator   operator-=(int rhs) {return (*this = *this - rhs);};

        reference   operator[](int n) { return *(*this + n); };

        // size_type   operator-(iterator rhs) {return (_ptr - rhs._ptr);}

        // iterator   operator-(int rhs) {return iterator(_ptr - rhs);}
        // iterator   operator+(int rhs) {return iterator(_ptr + rhs);}

        operator    deque_reverse_iterator<const value_type> () const {
        return deque_reverse_iterator<const value_type>(const_cast<const value_type **>(_node), _curr - _first) ; }

        // operator const_iterator () const { return const_iterator(_node, _curr - _first) ; }

    private:
        pointer _curr;       
        pointer _first;     // the begin of the chunk
        pointer _last;      // the end of the chunk
        map_pointer _node;
        friend class Deque<T>;

};
}

#endif