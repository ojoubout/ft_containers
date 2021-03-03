#ifndef LIST_ITERATOR_HPP
# define LIST_ITERATOR_HPP

#include "../iterator_traits.hpp"
// #include "List.hpp"
namespace ft {
    
template <typename T> class List;

template <typename T, typename node_pointer>
class list_iterator : public ft::iterator<std::bidirectional_iterator_tag, T> {
    friend class List<T>;
    public:

        typedef typename ft::iterator<std::bidirectional_iterator_tag, T>::iterator_category  iterator_category;
        typedef typename ft::iterator<std::bidirectional_iterator_tag, T>::value_type         value_type;
        typedef typename ft::iterator<std::bidirectional_iterator_tag, T>::pointer            pointer;
        typedef typename ft::iterator<std::bidirectional_iterator_tag, T>::reference          reference;
        typedef typename ft::iterator<std::bidirectional_iterator_tag, T>::difference_type    difference_type;
        // typedef struct List_Node<value_type>*   node_pointer;

        list_iterator() : _ptr(NULL) {};
        list_iterator(node_pointer ptr) : _ptr(ptr) {};
        list_iterator &operator=(list_iterator const &other) {
            _ptr = other._ptr;
            return (*this);
        }

        reference   operator*() { return _ptr->content; };
        pointer     operator->() { return &_ptr->content; };
        // Prefix increment
        list_iterator& operator++() { _ptr = _ptr->next; return *this; }  
        // Postfix increment
        list_iterator operator++(int) { list_iterator tmp = *this; ++(*this); return tmp; }
        // Prefix decrement
        list_iterator& operator--() { _ptr = _ptr->prev; return *this; }  
        // Postfix decrement
        list_iterator operator--(int) { list_iterator tmp = *this; --(*this); return tmp; }

        bool    operator!=(list_iterator const & it) { return (_ptr != it._ptr); }
        bool    operator==(list_iterator const & it) { return (_ptr == it._ptr); }

        operator list_iterator<const value_type, node_pointer> () const { return list_iterator<const value_type, node_pointer>(_ptr) ; }

    private:
        node_pointer _ptr;
};

template <typename T, typename node_pointer>
class list_reverse_iterator : public ft::iterator<std::bidirectional_iterator_tag, T> {
    public:    

        typedef typename ft::iterator<std::bidirectional_iterator_tag, T>::iterator_category  iterator_category;
        typedef typename ft::iterator<std::bidirectional_iterator_tag, T>::value_type         value_type;
        typedef typename ft::iterator<std::bidirectional_iterator_tag, T>::pointer            pointer;
        typedef typename ft::iterator<std::bidirectional_iterator_tag, T>::reference          reference;
        typedef typename ft::iterator<std::bidirectional_iterator_tag, T>::difference_type    difference_type;
        // typedef struct List_Node<value_type>*   node_pointer;

        list_reverse_iterator(node_pointer ptr) : _ptr(ptr) {};

        reference   operator*() { return _ptr->prev->content; };
        pointer     operator->() { return &_ptr->prev->content; };
        // Prefix increment
        list_reverse_iterator& operator++() { _ptr = _ptr->prev; return *this; }  
        // Postfix increment
        list_reverse_iterator operator++(int) { list_reverse_iterator tmp = *this; ++(*this); return tmp; }
        // Prefix decrement
        list_reverse_iterator& operator--() { _ptr = _ptr->next; return *this; }  
        // Postfix decrement
        list_reverse_iterator operator--(int) { list_reverse_iterator tmp = *this; --(*this); return tmp; }

        // operator const_reverse_iterator  () const { return const_reverse_iterator (_ptr) ; }

        bool    operator!=(const list_reverse_iterator & it) { return (_ptr != it._ptr); }
        bool    operator==(const list_reverse_iterator & it) { return (_ptr == it._ptr); }
        
        operator list_reverse_iterator<const value_type, node_pointer> () const { return list_reverse_iterator<const value_type, node_pointer>(_ptr) ; }


    private:
        node_pointer _ptr;
};



}

#endif