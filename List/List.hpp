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

            node_pointer get_node() { return (_ptr); };

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

            bool    operator!=(iterator const & it) { return (_ptr != it._ptr); }
            bool    operator==(iterator const & it) { return (_ptr == it._ptr); }

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

    List() {
        init();
    }


    List(const List & copy) {
        init();
        *this = copy;
    }

    List(size_type n, const value_type& val = value_type()) {
        init();
        insert(begin(), n, val);
    }

    List(const_iterator first, const_iterator last) {
        init();
        insert(begin(), first, last);
    }



    ~List() { // TODO: clear()
        clear();
        delete _end;
    }

    List&   operator=(const List& x) { // TODO: after finishing clear()
        clear();
        insert(begin(), x.begin(), x.end());
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

    void assign (const_iterator first, const_iterator last) {
        clear();
        insert(end(), first, last);
    }
    void assign (size_type n, const value_type& val) {
        clear();
        insert(end(), n, val);
    }

    void push_front (const value_type& val) {
        _begin = insert(iterator(_begin), val).get_node();
    }

    void pop_front() {
        if (_size) {
            _begin = erase(begin()).get_node();
        }
    }

    void push_back (const value_type& val) {
        iterator it = insert(end(), val);
        if (_size == 1) {
            _begin = it.get_node();
        }
    }

    void pop_back() {
        if (_size) {
            erase(--end());
        }
    }
    
    iterator insert (iterator position, const value_type& val) {
        node_pointer node_pos = position.get_node();
        node_pointer tmp = new node(val);

        if (node_pos->prev) {
            node_pos->prev->next = tmp;
        }
        tmp->prev = node_pos->prev;
        tmp->next = node_pos;
        node_pos->prev = tmp;
        if (node_pos == _begin)
            _begin = tmp;
        _size++;
        return (iterator(tmp));
    }

    void insert (iterator position, size_type n, const_reference val) {
        for (size_type i = 0; i < n; i++) {
            insert(position, val);
        }
    }

    void insert (iterator position, const_iterator first, const_iterator last) {
        while (first != last) {
            insert(position, *first++);
        }
    }

    iterator erase (iterator position) {
        node_pointer node_pos = position.get_node();
        if (node_pos == _end)
            return (_end);
        iterator ret = ++position;
        if (node_pos->next) {
            node_pos->next->prev = node_pos->prev;
        }
        if (node_pos->prev) {
            node_pos->prev->next = node_pos->next;
        }
        if (node_pos == _begin) {
            _begin = node_pos->next;
        }
        delete node_pos;
        _size--;
        return (ret);
    }

    iterator erase (iterator first, iterator last) {
        while (first != last) {
            erase(first++);
        }
        return (last);
    }

    void swap (List& x) {
        node_pointer    sbegin = _begin;
        node_pointer    send = _end;
        size_type       ssize = _size;

        _begin = x._begin;
        _end = x._end;
        _size = x._size;
        x._begin = sbegin;
        x._end = send;
        x._size = ssize;
    }

    void resize (size_type n, value_type val = value_type()) {
        if (n <= _size) {
            for (size_type i = _size; i > n; i--) {
                pop_back();
            }   
        } else {
            insert(end(), n - _size, val);
        }
    }

    void clear() {
        erase(begin(), end());
    }

    void splice (iterator position, List& x) {
            splice(position, x, x.begin(), x.end());
    }

    void splice (iterator position, List& x, iterator i) {
        node_pointer node_pos = position.get_node();
        node_pointer x_pos = i.get_node();
        if (x_pos == x._end) {
            return ;
        }
        if (x_pos->prev) {
            x_pos->prev->next = x_pos->next;
        }
        if (x_pos->next) {
            x_pos->next->prev = x_pos->prev;
        }
        if (node_pos->prev) {
            node_pos->prev->next = x_pos;
        }
        if (x_pos == x._begin) {
            x._begin = x_pos->next;
        }
        if (node_pos == _begin) {
            _begin = x_pos;
        }
        x_pos->prev = node_pos->prev;
        x_pos->next = node_pos;
        node_pos->prev = x_pos;
        _size++;
        x._size--;
    }

    void splice (iterator position, List& x, iterator first, iterator last) {
        while (first != last) {
            splice(position, x, first++);
        }
    }

    void remove (const value_type& val) {
        node_pointer tmp = _begin;
        while (tmp != _end) {
            if (tmp->content == val) {
                tmp = erase(tmp).get_node();
            } else {
                tmp = tmp->next;
            }
        }
    }

    template <class Predicate>
    void remove_if (Predicate pred) {
        node_pointer tmp = _begin;
        while (tmp != _end) {
            if (pred(tmp->content)) {
                tmp = erase(tmp).get_node();
            } else {
                tmp = tmp->next;
            }
        }
    }

    void unique() {
        node_pointer tmp = _begin;
        while (tmp != _end) {
            if (tmp->prev && tmp->content == tmp->prev->content) {
                tmp = erase(tmp).get_node();
            } else {
                tmp = tmp->next;
            }
        }
    }

    template <class BinaryPredicate>
    void unique (BinaryPredicate binary_pred) {
        node_pointer tmp = _begin;
        while (tmp != _end) {
            if (tmp->prev && binary_pred(tmp->content, tmp->prev->content)) {
                tmp = erase(tmp).get_node();
            } else {
                tmp = tmp->next;
            }
        }
    }

    void merge (List& x) {
        splice(end(), x);
    }

    template <class Compare>
    void merge (List& x, Compare comp) {
        iterator it = begin();
        value_type item = x._begin->content;
        while (it != end() && !comp(item, *it))
        {
            ++it;
        }
        splice(it, x);
    }

    void sort() {
        sort(operator<);
    }

    template <class Compare>
    void sort (Compare comp) {
        iterator it = begin();
        iterator ite = end();
        while (it != ite) {
            if (comp(*it, *it->next))
        }

    }


    // Operators Overload




private:
    node_pointer    _begin;
    node_pointer    _end;
    size_type       _size;

    void    init() {
        pointer val = static_cast<pointer>(::operator new(sizeof(value_type)));
        _end = new node(*val);
        _begin = _end;
        _end->prev = _end->next = NULL;
        _size = 0;
        free(val);
    }

}; // List class


template <class T>
bool operator== (const List<T>& lhs, const List<T>& rhs) {
    typename List<T>::iterator lhs_it = lhs.begin();
    typename List<T>::iterator lhs_ite = lhs.end();
    typename List<T>::iterator rhs_it = rhs.begin();
    typename List<T>::iterator rhs_ite = rhs.end();
    if (rhs._size != rhs._size)
        return (false);
    while (lhs_it != lhs_ite) {
        if (*lhs_it++ != *rhs_it++)
            return (false);
    }
    return (true);
}

template <class T>
bool operator!= (const List<T>& lhs, const List<T>& rhs) {
    return !(lhs == rhs);
}

template <class T>
bool operator<  (const List<T>& lhs, const List<T>& rhs) {
    typename List<T>::iterator lhs_it = lhs.begin();
    typename List<T>::iterator lhs_ite = lhs.end();
    typename List<T>::iterator rhs_it = rhs.begin();
    typename List<T>::iterator rhs_ite = rhs.end();
    while (lhs_it != lhs_ite && rhs_it != rhs_ite) {
        if (*lhs_it < *rhs_it)
            return (true);
        lhs_it++;
        rhs_it++;
    }
    if (lhs_it == lhs_ite)
        return (true);
    return (false);

}

template <class T>
bool operator<= (const List<T>& lhs, const List<T>& rhs) {
    return !(lhs > rhs);
}

template <class T>
bool operator>  (const List<T>& lhs, const List<T>& rhs) {
    return (rhs < lhs);
}

template <class T>
bool operator>= (const List<T>& lhs, const List<T>& rhs) {
    return !(lhs < rhs);
}

} // ft namespace

#endif