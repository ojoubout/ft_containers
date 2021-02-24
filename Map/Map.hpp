#ifndef MAP_HPP
# define MAP_HPP

#include "Pair.hpp"
#include "RedBlackTree.hpp"

namespace ft
{

template <class T> struct less {
  bool operator() (const T& x, const T& y) const {return x<y;}
};


template <typename Key, typename T, class Compare = less<Key> >
class Map {
public:
    typedef Key                                 key_type;
    typedef T                                   mapped_type;
    typedef Pair<const key_type, mapped_type>   value_type;
    typedef Compare                             key_compare;
    typedef Compare                             value_compare;
    // typedef struct List_Node<value_type>        node;
    // typedef struct List_Node<value_type>*       node_pointer;
    typedef value_type*                         pointer;
    typedef const value_type*                   const_pointer;
    typedef value_type&                         reference;
    typedef const value_type&                   const_reference;
    typedef size_t                              size_type;
    typedef ptrdiff_t                           difference_type;

    explicit Map (const key_compare& comp = key_compare()) {} ;

    // template <class InputIterator>
    // Map (InputIterator first, InputIterator last, const key_compare& comp = key_compare());
    Map (const Map& x) {
        *this = x;
    }

    Map&    operator=(const Map& x) {
        clear();
        _map = x._map;
    }

    void    clear() {
        _map.clear();
    }


private:
    RedBlackTree<value_type>    _map;
        
};
} // namespace ft

#endif