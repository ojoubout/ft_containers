#ifndef LIST_HPP
# define LIST_HPP

#include <algorithm>
#include <limits>
#include <cstddef>

namespace ft {

template <typename T>
struct List_Node {
    T                   content;
    struct List_Node    *next;
    struct List_Node    *prev;
    List_Node(const T &val) : content(val) {};
};

template <typename T>
class List {
public:

    typedef T                       value_type;
    typedef struct List_Node<T>     node;
    typedef struct List_Node<T>*    node_pointer;
    typedef value_type*             pointer;
    typedef const value_type*       const_pointer;
    typedef value_type&             reference;
    typedef const value_type&       const_reference;
    typedef size_t                  size_type;
    typedef ptrdiff_t               difference_type;

    struct const_iterator {
        public:

            typedef std::bidirectional_iterator_tag iterator_catagory;
            typedef std::ptrdiff_t                  difference_type;
            typedef List::value_type                value_type;
            typedef const T*             pointer;
            typedef const T&           reference;
    
            const_iterator(node_pointer ptr) : _ptr(ptr) {};

            reference   operator*() { return _ptr->content; };
            pointer     operator->() { return &_ptr->content; };
            // Prefix increment
            const_iterator& operator++() { _ptr = _ptr->next; return *this; }  
            // Postfix increment
            const_iterator operator++(int) { const_iterator tmp = *this; ++(*this); return tmp; }
            // Prefix decrement
            const_iterator& operator--() { _ptr = _ptr->prev; return *this; }  
            // Postfix decrement
            const_iterator operator--(int) { const_iterator tmp = *this; --(*this); return tmp; }


            bool    operator!=(const_iterator & it) { return (_ptr != it._ptr); }
            bool    operator==(const_iterator & it) { return (_ptr == it._ptr); }


        protected:
            node_pointer _ptr;
    };
    struct iterator {
        public:

            typedef std::bidirectional_iterator_tag iterator_catagory;
            typedef std::ptrdiff_t                  difference_type;
            typedef List::value_type                value_type;
            typedef List::pointer                   pointer;
            typedef List::reference                 reference;
    
            iterator(node_pointer ptr) : _ptr(ptr) {};

            node_pointer get_node() const { return (_ptr); };

            reference   operator*() { return _ptr->content; };
            pointer     operator->() { return &_ptr->content; };
            // Prefix increment
            iterator& operator++() { _ptr = _ptr->next; return *this; }  
            // Postfix increment
            iterator operator++(int) { iterator tmp = *this; ++(*this); return tmp; }
            // Prefix decrement
            iterator& operator--() { _ptr = _ptr->prev; return *this; }  
            // Postfix decrement
            iterator operator--(int) { iterator tmp = *this; --(*this); return tmp; }

            bool    operator!=(iterator & it) { return (_ptr != it._ptr); }
            bool    operator==(iterator & it) { return (_ptr == it._ptr); }

            operator const_iterator () const { return const_iterator(_ptr) ; }

        private:
            node_pointer _ptr;
    };

    struct const_reverse_iterator  {
        public:

            typedef std::bidirectional_iterator_tag iterator_catagory;
            typedef std::ptrdiff_t                  difference_type;
            typedef List::value_type                value_type;
            typedef const T*                   pointer;
            typedef const T&                 reference;
    
            const_reverse_iterator (node_pointer ptr) : _ptr(ptr) {};

            reference   operator*() { return _ptr->content; };
            pointer     operator->() { return &_ptr->content; };
            // Prefix increment
            const_reverse_iterator & operator++() { _ptr = _ptr->prev; return *this; }  
            // Postfix increment
            const_reverse_iterator  operator++(int) { const_reverse_iterator  tmp = *this; ++(*this); return tmp; }
            // Prefix decrement
            const_reverse_iterator & operator--() { _ptr = _ptr->next; return *this; }  
            // Postfix decrement
            const_reverse_iterator  operator--(int) { const_reverse_iterator  tmp = *this; --(*this); return tmp; }

            bool    operator!=(const_reverse_iterator & it) { return (_ptr != it._ptr); }
            bool    operator==(const_reverse_iterator & it) { return (_ptr == it._ptr); }


        private:
            node_pointer _ptr;
    };

    struct reverse_iterator {
        public:

            typedef std::bidirectional_iterator_tag iterator_catagory;
            typedef std::ptrdiff_t                  difference_type;
            typedef List::value_type                value_type;
            typedef List::pointer                   pointer;
            typedef List::reference                 reference;
    
            reverse_iterator(node_pointer ptr) : _ptr(ptr) {};

            reference   operator*() { return _ptr->prev->content; };
            pointer     operator->() { return &_ptr->prev->content; };
            // Prefix increment
            reverse_iterator& operator++() { _ptr = _ptr->prev; return *this; }  
            // Postfix increment
            reverse_iterator operator++(int) { reverse_iterator tmp = *this; ++(*this); return tmp; }
            // Prefix decrement
            reverse_iterator& operator--() { _ptr = _ptr->next; return *this; }  
            // Postfix decrement
            reverse_iterator operator--(int) { reverse_iterator tmp = *this; --(*this); return tmp; }

            operator const_reverse_iterator  () const { return const_reverse_iterator (_ptr) ; }

            bool    operator!=(reverse_iterator & it) { return (_ptr != it._ptr); }
            bool    operator==(reverse_iterator & it) { return (_ptr == it._ptr); }


        private:
            node_pointer _ptr;
    };



    // typedef iterator const          const_iterator;


    // List();
    // List(size_t *n, const value_type& val);
    // template <class InputIterator>
    // List (InputIterator first, InputIterator last);
    // List(const List& copy);
    // ~List();

    
    List() : _size(0) {
        pointer val = static_cast<pointer>(::operator new(sizeof(value_type)));
        _end = new node(*val);
        _begin = _end;
        _end->prev = _end->next = NULL;
    }


    List(const List & copy) {
        *this = copy;
    }


    template <typename InputIterator>
    List(InputIterator first, InputIterator last) {
        node_pointer tmp = _begin;
        for (InputIterator it = first; it != last; ++it) {
            if (tmp == _begin) {
                _begin = new node(*it);
                // _begin->content = *it;
                _begin->next = NULL;
                tmp = _begin;
            } else {
                tmp->next = new node(*it);
                // tmp->next->content = *it;
                tmp->next->next = NULL;
                tmp = tmp->next;
            }
        }
    }



    ~List() { // TODO: clear()
    }


    List&   operator=(const List& x) { // TODO: after finishing clear()
        (void)x;
        return (*this);
    }

    // Iterators: 

    const_iterator begin() const {
        return (const_iterator(_begin));
    }
    iterator begin() {
        return (iterator(_begin));
    }
    const_iterator end() const {
        return (const_iterator(_end));
    }
    iterator end() {
        return (iterator(_end));
    }
    const_reverse_iterator rbegin() const {
        return (const_reverse_iterator(_end));
    }
    const_reverse_iterator rend() const {
        return (const_reverse_iterator(_begin));
    }
    reverse_iterator rbegin() {
        return (reverse_iterator(_end));
    }
    reverse_iterator rend() {
        return (reverse_iterator(_begin));
    }

    // Capacity:

    bool    empty() const {
        return (_size == 0);
    }

    size_type size() const {
        return (_size);
    }

    size_type       max_size() const {
        return (std::numeric_limits<difference_type>::max());
    }

    // Element access:

    reference       front() {
        return (_begin->content);
    }

    const_reference front() const {
        return (_begin->content);
    }

    reference       back() {
        if (_size)
            return (_end->prev->content);
        return (_end->content);
    }

    const_reference back() const {
        if (_size)
            return (_end->prev->content);
        return (_end->content);
    }

    // Modifiers:
    void clear();

    template <class InputIterator>
    void assign (InputIterator first, InputIterator last) {
        clear();
        for (InputIterator it = first; it != last; ++it) {
            push_back(*it);
        }
    }
    void assign (size_type n, const value_type& val) {
        clear();
        for (size_type i = 0; i < n; i++) {
            push_back(val);
        }
    }


    void push_front (const value_type& val) {
        node_pointer tmp = new node(val);
        // tmp->content = val;
        tmp->next = _begin;
        _begin->prev = tmp;
        _begin = tmp;
        _size++;
    }

    void pop_front() {
        if (_size) {
            node_pointer tmp = _begin;
            _begin = _begin->next;
            _begin->prev = NULL;
            delete tmp;
            _size--;
        }
    }

    void push_back (const value_type& val) {
        if (_size == 0) {
            _begin = new node(val);
            _begin->next = _end;
            _end->prev = _begin;
        } else {
            node_pointer tmp = new node(val);
            tmp->next = _end;
            tmp->prev = _end->prev;
            tmp->prev->next = tmp;
            _end->prev = tmp;
        }
        // _end->content = val;
        _end->next = NULL;
        _size++;
    }

    void pop_back() {
        if (_size) {
            node_pointer tmp = _end->prev;
            _end->prev = tmp->prev;
            if (tmp->prev) {
                tmp->prev->next = _end;
            }
            delete tmp;
            _size--;
        }
    }

    iterator insert (iterator position, const value_type& val) {
        node_pointer node = position.get_node();
        node_pointer tmp = new node(val);
        if (node->prev) {
            node->prev->next = tmp;
        }
        tmp->prev = node->prev;
        tmp->next = node;
        node->prev = tmp;
    }

    // void insert (iterator position, size_type n, const value_type& val);

    // template <class InputIterator>
    // void insert (iterator position, InputIterator first, InputIterator last);



private:
    node_pointer    _begin;
    node_pointer    _end;
    size_type       _size;

}; // List class

} // ft namespace

#endif