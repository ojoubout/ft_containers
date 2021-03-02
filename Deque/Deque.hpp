#ifndef DEQUE_HPP
# define DEQUE_HPP

#include <cstddef>
#include "../iterator_traits.hpp"

namespace ft {

template < class T >
class Deque {
public:

    typedef T               value_type;
    typedef T&              reference;
    typedef const T&        const_reference;
    typedef T*              pointer;
    typedef T**             map_pointer;
    typedef const T*        const_pointer;
    typedef std::ptrdiff_t  difference_type;
    typedef size_t          size_type;

    static const size_type  buff_size = 16;

    struct const_iterator : public ft::iterator<std::random_access_iterator_tag, const T> {
        public:    
           
            typedef typename ft::iterator<std::random_access_iterator_tag, const T>::iterator_category  iterator_category;
            typedef typename ft::iterator<std::random_access_iterator_tag, const T>::value_type         value_type;
            typedef typename ft::iterator<std::random_access_iterator_tag, const T>::pointer            pointer;
            typedef typename ft::iterator<std::random_access_iterator_tag, const T>::reference          reference;
            typedef typename ft::iterator<std::random_access_iterator_tag, const T>::difference_type    difference_type;

            const_iterator() : _ptr(NULL) {};
            const_iterator(const_pointer ptr) : _ptr(ptr) {};
            const_iterator &operator=(const_iterator const &other) {
                _ptr = other._ptr;
                return (*this);
            }


            const_reference   operator*() { return *_ptr; };
            const_pointer     operator->() { return _ptr; };
            // Prefix increment
            const_iterator& operator++() { ++_ptr; return *this; }  
            // Postfix increment
            const_iterator operator++(int) { const_iterator tmp = *this; ++(*this); return tmp; }
            // Prefix decrement
            const_iterator& operator--() { --_ptr; return *this; }  
            // Postfix decrement
            const_iterator operator--(int) { const_iterator tmp = *this; --(*this); return tmp; }

            size_type   operator-(const_iterator rhs) {return (_ptr - rhs._ptr);}

            const_iterator   operator-(int rhs) {return const_iterator(_ptr - rhs);}
            const_iterator   operator+(int rhs) {return const_iterator(_ptr + rhs);}


            bool    operator!=(const const_iterator & it) { return (_ptr != it._ptr); }
            bool    operator==(const const_iterator & it) { return (_ptr == it._ptr); }


        private:
            const_pointer _ptr;
    };
    struct iterator : public ft::iterator<std::random_access_iterator_tag, T> {
        public:    

            typedef typename ft::iterator<std::random_access_iterator_tag, T>::iterator_category  iterator_category;
            typedef typename ft::iterator<std::random_access_iterator_tag, T>::value_type         value_type;
            typedef typename ft::iterator<std::random_access_iterator_tag, T>::pointer            pointer;
            typedef typename ft::iterator<std::random_access_iterator_tag, T>::reference          reference;
            typedef typename ft::iterator<std::random_access_iterator_tag, T>::difference_type    difference_type;

            // iterator() : _ptr() {};
            iterator(map_pointer map, size_type index) {
                set_node(map);
                _curr = _first + index;
            };

            iterator &operator=(const iterator &other) {
                set_node(other._node);
                _curr = other._curr;
                return (*this);
            }

            void    set_node(map_pointer map) {
                _node = map;
                _first = *map;
                _last = _first + buff_size;
            }


            reference   operator*() { return *_curr; };
            pointer     operator->() { return _curr; };
            // Prefix increment
            iterator& operator++() {
                ++_curr;
                if (_curr == _last) {
                    set_node(_node + 1);
                    _curr = _first;
                } 
                return *this;
            }
            // Postfix increment
            iterator operator++(int) { iterator tmp = *this; ++(*this); return tmp; }
            // Prefix decrement
            iterator& operator--() {
                if (_curr == _first) {
                    set_node(_node - 1);
                    _curr = _last;
                }
                --_curr;
                return *this;
            }  
            // Postfix decrement
            iterator operator--(int) { iterator tmp = *this; --(*this); return tmp; }

            bool    operator!=(const iterator & it) { return (_curr != it._curr); }
            bool    operator==(const iterator & it) { return (_curr == it._curr); }

            // size_type   operator-(iterator rhs) {return (_ptr - rhs._ptr);} // LAST

            // iterator   operator-(int rhs) {return iterator(_ptr - rhs);}
            // iterator   operator+(int rhs) {return iterator(_ptr + rhs);}


            // operator const_iterator () const { return const_iterator(_node, _curr - _first) ; }

        private:
            pointer _curr;       
            pointer _first;     // the begin of the chunk
            pointer _last;      // the end of the chunk
            map_pointer _node;

    };

    struct const_reverse_iterator : public ft::iterator<std::random_access_iterator_tag, const T> {
        public:    

            typedef typename ft::iterator<std::random_access_iterator_tag, const T>::iterator_category  iterator_category;
            typedef typename ft::iterator<std::random_access_iterator_tag, const T>::value_type         value_type;
            typedef typename ft::iterator<std::random_access_iterator_tag, const T>::pointer            pointer;
            typedef typename ft::iterator<std::random_access_iterator_tag, const T>::reference          reference;
            typedef typename ft::iterator<std::random_access_iterator_tag, const T>::difference_type    difference_type;

            const_reverse_iterator (const_pointer ptr) : _ptr(ptr) {};

            const_reference   operator*() { return *(_ptr - 1); };
            const_pointer     operator->() { return (_ptr - 1); };
            // Prefix increment
            const_reverse_iterator & operator++() { --_ptr; return *this; }  
            // Postfix increment
            const_reverse_iterator  operator++(int) { const_reverse_iterator  tmp = *this; ++(*this); return tmp; }
            // Prefix decrement
            const_reverse_iterator & operator--() { ++_ptr; return *this; }  
            // Postfix decrement
            const_reverse_iterator  operator--(int) { const_reverse_iterator  tmp = *this; --(*this); return tmp; }

            bool    operator!=(const const_reverse_iterator & it) { return (_ptr != it._ptr); }
            bool    operator==(const const_reverse_iterator & it) { return (_ptr == it._ptr); }

            const_reverse_iterator   operator-(int rhs) {return const_reverse_iterator(_ptr + rhs);}
            const_reverse_iterator   operator+(int rhs) {return const_reverse_iterator(_ptr - rhs);}


        private:
            const_pointer _ptr;
    };

    struct reverse_iterator : public ft::iterator<std::random_access_iterator_tag, T> {
        public:

            typedef typename ft::iterator<std::random_access_iterator_tag, T>::iterator_category  iterator_category;
            typedef typename ft::iterator<std::random_access_iterator_tag, T>::value_type         value_type;
            typedef typename ft::iterator<std::random_access_iterator_tag, T>::pointer            pointer;
            typedef typename ft::iterator<std::random_access_iterator_tag, T>::reference          reference;
            typedef typename ft::iterator<std::random_access_iterator_tag, T>::difference_type    difference_type;

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

            bool    operator!=(const reverse_iterator & it) { return (_ptr != it._ptr); }
            bool    operator==(const reverse_iterator & it) { return (_ptr == it._ptr); }

            reverse_iterator   operator-(int rhs) {return reverse_iterator(_ptr + rhs);}
            reverse_iterator   operator+(int rhs) {return reverse_iterator(_ptr - rhs);}

            operator const_reverse_iterator  () const { return const_reverse_iterator (_ptr) ; }


        private:
            pointer _ptr;
    };

    explicit Deque() {
        init();
    }

    explicit Deque (size_type n, const value_type& val = value_type());

    template <class InputIterator>
    Deque (InputIterator first, InputIterator last);

    Deque (const Deque& x) {
        *this = x;
    }

    ~Deque() {
        
    }

    Deque& operator= (const Deque& x);

    // template <class InputIterator>
    // void assign (InputIterator first, InputIterator last);

    void assign (size_type n, const value_type& val) {
        clear();
        _last_chunk_size = n % buff_size;
        _map_size = _last_chunk_size != 0 ? (n / buff_size) + 1 : (n / buff_size);
        _map = new pointer[_map_size];
        for (size_type i = 0; i < _map_size; i++) {
            _map[i] = static_cast<pointer>(::operator new(sizeof(value_type) * buff_size));
            for (size_type j = 0; j < buff_size && n > 0; j++, n--) {
                _map[i][j] = val;
            }
        }
    }

    void print() {
        std::cout << "_map_size:        " << _map_size << std::endl;
        std::cout << "_last_chunk_size: " << _last_chunk_size << std::endl;
        for (size_type i = 0; i < _map_size; i++) {
            size_type max = (_last_chunk_size && i == _map_size - 1) ? _last_chunk_size : buff_size;
            for (size_type j = 0; j < max; j++) {
                std::cout << _map[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }

    void clear() {
    }

private:
    
        map_pointer     _map;
        size_type       _map_size;
        size_type       _last_chunk_size;
        void    init() {
            _map = static_cast<map_pointer>(::operator new(0));;
            _map_size = 0;
            _last_chunk_size = 0;
        }

        // size_type   capacity() {
        //     return(_map_size * );
        // }
};

} // ft namespace

#endif