#pragma once
#ifndef MAP_HPP
# define MAP_HPP

#include "../Pair.hpp"
#include "RedBlackTree.hpp"

namespace ft
{

template <typename Key, typename T, class Compare = less<Key> >
class Map {
public:
    typedef Key                                             key_type;
    typedef T                                               mapped_type;
    typedef ft::Pair<key_type, mapped_type>                 value_type;
    typedef Compare                                         key_compare;
    typedef value_type*                                     pointer;
    typedef const value_type*                               const_pointer;
    typedef value_type&                                     reference;
    typedef const value_type&                               const_reference;
    typedef size_t                                          size_type;
    typedef std::ptrdiff_t                                  difference_type;

    // typedef struct List_Node<value_type>                 node;
    
    struct value_comp {
        bool operator() (const value_type& x, const value_type& y) const {
            return key_compare()(x.first, y.first);
        }
    };

    typedef value_comp                          value_compare;
    typedef typename RedBlackTree<value_type, value_compare>::Node*  node_pointer;

    typedef typename RedBlackTree<value_type, value_compare>::iterator                  iterator;
    typedef typename RedBlackTree<value_type, value_compare>::const_iterator            const_iterator;
    typedef typename RedBlackTree<value_type, value_compare>::reverse_iterator          reverse_iterator;
    typedef typename RedBlackTree<value_type, value_compare>::const_reverse_iterator    const_reverse_iterator;
    // Iterators

    // struct const_iterator : public iterator_traits<T> {
    //     public:    
    //         const_iterator() : _ptr(NULL) {};
    //         const_iterator(node_pointer ptr) : _ptr(ptr) {};
    //         const_iterator &operator=(const_iterator const &other) {
    //             _ptr = other._ptr;
    //             return (*this);
    //         }


    //         reference   operator*() { return _ptr->item; };
    //         pointer     operator->() { return &_ptr->item; };
    //         // Prefix increment
    //         const_iterator& operator++() { _ptr = _ptr->getNext(); return *this; }  
    //         // Postfix increment
    //         const_iterator operator++(int) { const_iterator tmp = *this; ++(*this); return tmp; }
    //         // Prefix decrement
    //         const_iterator& operator--() { _ptr = _ptr->getPrevious(); return *this; }  
    //         // Postfix decrement
    //         const_iterator operator--(int) { const_iterator tmp = *this; --(*this); return tmp; }


    //         bool    operator!=(const_iterator & it) { return (_ptr != it._ptr); }
    //         bool    operator==(const_iterator & it) { return (_ptr == it._ptr); }


    //     protected:
    //         node_pointer _ptr;
    // };
    // struct iterator : public iterator_traits<T> {
    //     public:
    //         iterator() : _ptr(NULL) {};
    //         iterator(node_pointer ptr) : _ptr(ptr) {};
    //         iterator &operator=(iterator const &other) {
    //             _ptr = other._ptr;
    //             return (*this);
    //         }


    //         node_pointer get_node() { return (_ptr); };

    //         reference   operator*() { return _ptr->item; };
    //         pointer     operator->() { return &_ptr->item; };
    //         // Prefix increment
    //         iterator& operator++() { _ptr = _ptr->getNext(); return *this; }  
    //         // Postfix increment
    //         iterator operator++(int) { iterator tmp = *this; ++(*this); return tmp; }
    //         // Prefix decrement
    //         iterator& operator--() { _ptr = _ptr->getPrevious(); return *this; }  
    //         // Postfix decrement
    //         iterator operator--(int) { iterator tmp = *this; --(*this); return tmp; }

    //         bool    operator!=(iterator const & it) { return (_ptr != it._ptr); }
    //         bool    operator==(iterator const & it) { return (_ptr == it._ptr); }

    //         operator const_iterator () const { return const_iterator(_ptr) ; }

    //     private:
    //         node_pointer _ptr;
    // };

    // struct const_reverse_iterator : public iterator_traits<T> {
    //     public:    
    //         const_reverse_iterator (node_pointer ptr) : _ptr(ptr) {};

    //         reference   operator*() { return _ptr->item; };
    //         pointer     operator->() { return &_ptr->item; };
    //         // Prefix increment
    //         const_reverse_iterator & operator++() { _ptr = _ptr->getPrevious(); return *this; }  
    //         // Postfix increment
    //         const_reverse_iterator  operator++(int) { const_reverse_iterator  tmp = *this; ++(*this); return tmp; }
    //         // Prefix decrement
    //         const_reverse_iterator & operator--() { _ptr = _ptr->getNext(); return *this; }  
    //         // Postfix decrement
    //         const_reverse_iterator  operator--(int) { const_reverse_iterator  tmp = *this; --(*this); return tmp; }

    //         bool    operator!=(const_reverse_iterator & it) { return (_ptr != it._ptr); }
    //         bool    operator==(const_reverse_iterator & it) { return (_ptr == it._ptr); }


    //     private:
    //         node_pointer _ptr;
    // };

    // struct reverse_iterator : public iterator_traits<T> {
    //     public:    
    //         reverse_iterator(node_pointer ptr) : _ptr(ptr) {};

    //         reference   operator*() { return _ptr->prev->item; };
    //         pointer     operator->() { return &_ptr->prev->item; };
    //         // Prefix increment
    //         reverse_iterator& operator++() { _ptr = _ptr->getPrevious(); return *this; }  
    //         // Postfix increment
    //         reverse_iterator operator++(int) { reverse_iterator tmp = *this; ++(*this); return tmp; }
    //         // Prefix decrement
    //         reverse_iterator& operator--() { _ptr = _ptr->getNext(); return *this; }  
    //         // Postfix decrement
    //         reverse_iterator operator--(int) { reverse_iterator tmp = *this; --(*this); return tmp; }

    //         operator const_reverse_iterator  () const { return const_reverse_iterator (_ptr) ; }

    //         bool    operator!=(reverse_iterator & it) { return (_ptr != it._ptr); }
    //         bool    operator==(reverse_iterator & it) { return (_ptr == it._ptr); }


    //     private:
    //         node_pointer _ptr;
    // };

    explicit Map (const key_compare& comp = key_compare()) : _key_comp(comp) {} ;

    template <class InputIterator>
    Map (InputIterator first, InputIterator last, const key_compare& comp = key_compare()) : _key_comp(comp) {
        insert(first, last);
    }
    Map (const Map& x) {
        *this = x;
    }

    Map&    operator=(const Map& x) {
        clear();
        _map = x._map;
        _key_comp = x._key_comp;
        return (*this);
    }

    const_iterator begin() const {
        return (_map.begin());
    }
    iterator begin() {
        return (_map.begin());
    }
    const_iterator end() const {
        return (_map.end());
    }
    iterator end() {
        return (_map.end());
    }
    const_reverse_iterator rbegin() const {
        return (_map.rbegin());
    }
    const_reverse_iterator rend() const {
        return (_map.rend());
    }
    reverse_iterator rbegin() {
        return (_map.rbegin());
    }
    reverse_iterator rend() {
        return (_map.rend());
    }

    // Capacity

    bool empty() const {
        return (_map.size() == 0);
    }

    size_type size() const {
        return _map.size();
    }

    size_type max_size() const {
        return (_map.max_size());
    }

    // Element Access

    mapped_type& operator[] (const key_type& k) {
        iterator found = find(k);
        if (found != end())
            return (*found).second;
        value_type  x = value_type(k, mapped_type());
        return ((*insert(x).first).second);
    }


    // const_iterator begin() const;

    void print() {
        _map.printTree(NULL, NULL, false);
    }
    void printOrder() {
        _map.printOrder();
    }
    void printReverseOrder() {
        _map.printReverseOrder();
    }

    // Modifiers

    Pair<iterator, bool> insert (const value_type& val) {
        return _map.insert(val);
    }

    iterator insert (iterator pos, const value_type& val) {
        return _map.insert(pos, val);
    }

    // iterator insert (iterator position, const value_type& val);

    template <class InputIterator>
    void insert (InputIterator first, InputIterator last) {
        while (first != last) {
            insert(*(first++));
        }
    }

    void erase (iterator position) {
        _map.erase(position, *position);
    }

    size_type erase (const key_type& k) {
        return _map.erase(value_type(k, mapped_type()));
    }
    void erase (iterator first, iterator last) {
        while (first != last) {
            _map.erase(*(first++));
        }

    }

    void swap (Map& x) {
        _map.swap(x._map);
    }


    void    clear() {
        _map.clear();
    }

    // Observers:

    key_compare key_comp() const {
        return (_key_comp);
    }

    value_compare value_comp() const {
        return _value_comp;
    }

    // Operations:

    iterator find (const key_type& k) {
        iterator res = lower_bound(k);
        return (res == end() || _key_comp(k, (*res).first) ? end() : res);
    }

    const_iterator find (const key_type& k) const {
        Map::const_iterator res = lower_bound(k);
        Map::const_iterator e = end();
        return (res == e || _key_comp(k, (*res).first) ? end() : res);
    }

    size_type count (const key_type& k) const {
        const_iterator f = find(k);
        const_iterator e = end();
        return (f != e);
    }

    iterator        lower_bound (const key_type& k) {
        iterator first = begin();
        iterator last = end();
        while (first != last) {
            if (_key_comp((*first).first, k) == false) {
                break;
            }
            ++first;
        }
        return (first);
    }
    const_iterator  lower_bound (const key_type& k) const {
        const_iterator first = begin();
        const_iterator last = end();
        while (first != last) {
            if (_key_comp((*first).first, k) == false) {
                break;
            }
            ++first;
        }
        return (first);
    }

    iterator upper_bound (const key_type& k) {
        iterator first = begin();
        iterator last = end();
        while (first != last) {
            if (_key_comp(k, (*first).first) == true) {
                break;
            }
            ++first;
        }
        return (first);
    }

    const_iterator upper_bound (const key_type& k) const {
        return upper_bound(k);
    }

    Pair<iterator,iterator>             equal_range (const key_type& k) {
        return (Pair<iterator,iterator>(lower_bound(k), upper_bound(k)));
    }

    Pair<const_iterator,const_iterator> equal_range (const key_type& k) const {
        return (Pair<const_iterator,const_iterator>(lower_bound(k), upper_bound(k)));
    }


private:
    RedBlackTree<value_type, value_compare> _map;
    key_compare     _key_comp;
    value_compare   _value_comp;

};
} // namespace ft

#endif