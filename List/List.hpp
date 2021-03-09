#ifndef LIST_HPP
# define LIST_HPP

#include <limits>
#include <cstddef>
#include "../utils/iterator_traits.hpp"
#include "../utils/utils.hpp"
#include "list_iterator.hpp"

namespace ft {

template <class T>
bool operator<  (const List<T>& lhs, const List<T>& rhs);


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

    typedef T                               value_type;
    typedef struct List_Node<value_type>             node;
    typedef struct List_Node<value_type>*            node_pointer;
    typedef value_type*                     pointer;
    typedef const value_type*               const_pointer;
    typedef value_type&                     reference;
    typedef const value_type&               const_reference;
    typedef size_t                          size_type;
    typedef ptrdiff_t                       difference_type;

    typedef list_iterator<value_type, node_pointer>                 iterator;
    typedef list_iterator<const value_type, node_pointer>           const_iterator;
    typedef list_reverse_iterator<value_type, node_pointer>         reverse_iterator;
    typedef list_reverse_iterator<const value_type, node_pointer>   const_reverse_iterator;

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

    template <class InputIterator>
    List(InputIterator first, InputIterator last,
    typename enable_if<!is_integral<InputIterator>::value, InputIterator>::type = 0) {
        init();
        insert(begin(), first, last);
    }

    ~List() {
        clear();
        delete _end;
    }

    List&   operator=(const List& x) {
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
        return (std::numeric_limits<size_type>::max() / (sizeof(List)));
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

    template <typename InputIterator>
    void assign (InputIterator first, InputIterator last,
    typename enable_if<!is_integral<InputIterator>::value, InputIterator>::type = 0) {
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

    template <typename InputIterator>
    void insert (iterator position, InputIterator first, InputIterator last,
    typename enable_if<!is_integral<InputIterator>::value, InputIterator>::type = 0) {
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
            if (tmp->prev && binary_pred(tmp->prev->content, tmp->content)) {
                tmp = erase(tmp).get_node();
            } else {
                tmp = tmp->next;
            }
        }
    }

    void merge (List& x) {
        merge(x, less_comp);
    }

    template <typename Compare>
    void merge (List& x, Compare comp) {
        if (this != &x) {
            iterator first1 = begin();
            iterator last1 = end();
            iterator first2 = x.begin();
            iterator last2 = x.end();
            while (first1 != last1 && first2 != last2)
                if (comp(*first2, *first1))
                {
                    iterator next = first2;
                    splice(first1, x, next++);
                    first2 = next;
                } else {
                    ++first1;
                }
            if (first2 != last2)
                splice(last1, x, first2, last2);
       }
    }

    template <typename Compare>
    void sort (Compare comp) {
        int count = _size;
        bool is_sort = true;
        while (count-- && is_sort) {
            is_sort = false;
            iterator it = begin();
            iterator ite = end();
            iterator next_it = it;
            ++next_it;
            while (it != ite && next_it != ite) {
                if (!comp(*it, *next_it)) {
                    node_pointer first = it.get_node();
                    node_pointer second = next_it.get_node();
                    node_pointer first_prev = first->prev;
                    node_pointer second_next = second->next;
                    if (first == _begin) {
                        _begin = second;
                    }
                    first->prev = second;
                    second->next = first;
                    second->prev = first_prev;
                    first->next = second_next;
                    if (first_prev) {
                        first_prev->next = second;
                    }
                    if (second_next) {
                        second_next->prev = first;
                    }
                    next_it = it;
                    ++next_it;
                    is_sort = true;
                } else {
                    ++next_it;
                    ++it;
                }
            }
        }
    }

    void sort() {
        sort(less_comp);
    }

    void reverse() {
        node_pointer curr = _end->prev;
        node_pointer tmp = NULL;
        if (curr)
            _begin = curr;
        while (curr) {
            tmp = curr->prev;
            curr->prev = curr->next;
            curr->next = tmp;
            if (tmp == NULL) {
                curr->next = _end;
                _end->prev = curr;
            }
            curr = tmp;
        }
        _begin->prev = NULL;

    }


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
        operator delete(val);
    }

    void swap_pos(node_pointer first, node_pointer second) {
        if (first == second || first == _end || second == _end) {
            return ;
        }
        node_pointer first_prev = first->prev;
        node_pointer first_next = first->next;
        first->prev = second->prev;
        first->next = second->next;
        second->prev = first_prev;
        second->next = first_next;
        if (first->prev) {
            first->prev->next = first;
        }
        if (first->next) {
            first->next->prev = first;
        }
        if (second->prev) {
            second->prev->next = second;
        }
        if (second->next) {
            second->next->prev = second;
        }
        if (first == _begin) {
            _begin = second;
        }
        if (second == _begin) {
            _begin = first;
        }
    }

    static bool less_comp(const value_type & first, const value_type & second) {
        return (first < second);
    }

}; // List class


// Relational operators

template <typename T>
bool operator== (const List<T>& lhs, const List<T>& rhs) {
    typename List<T>::const_iterator lhs_it = lhs.begin();
    typename List<T>::const_iterator lhs_ite = lhs.end();
    typename List<T>::const_iterator rhs_it = rhs.begin();
    if (lhs.size() != rhs.size())
        return (false);
    while (lhs_it != lhs_ite) {
        if (*lhs_it++ != *rhs_it++)
            return (false);
    }
    return (true);
}

template <typename T>
bool operator!= (const List<T>& lhs, const List<T>& rhs) {
    return !(lhs == rhs);
}

template <typename T>
bool operator<  (const List<T>& lhs, const List<T>& rhs) {
    typename List<T>::const_iterator lhs_it = lhs.begin();
    typename List<T>::const_iterator lhs_ite = lhs.end();
    typename List<T>::const_iterator rhs_it = rhs.begin();
    typename List<T>::const_iterator rhs_ite = rhs.end();
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

template <typename T>
bool operator<= (const List<T>& lhs, const List<T>& rhs) {
    return !(lhs > rhs);
}

template <typename T>
bool operator>  (const List<T>& lhs, const List<T>& rhs) {
    return (rhs < lhs);
}

template <typename T>
bool operator>= (const List<T>& lhs, const List<T>& rhs) {
    return !(lhs < rhs);
}

template<typename T>
void swap(List<T> &first, List<T> &second) {
	first.swap(second);
}

} // ft namespace

#endif
