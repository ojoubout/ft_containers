#ifndef REDBLACKTREE_HPP
# define REDBLACKTREE_HPP

#include <string>
#include <limits>
#include "../utils/Pair.hpp"
#include "../utils/iterator_traits.hpp"
#include "../utils/utils.hpp"

namespace ft {

template <typename T, class Compare = less<T> >
class RedBlackTree {
public:
    enum Color{RED, BLACK};
    // typedef struct Node          Node;

    struct Node
    {
        public:
            T               item;
            Color           color;
            struct Node *left, *right, *parent;
            Node(const T &val) : item(val), color(RED), left(NULL), right(NULL), parent(NULL) {};

            Node*   rightMost() const {
                const Node*   tmp = this;

                while (tmp->right) {
                    tmp = tmp->right;
                }
                return (const_cast<Node*>(tmp));
            }

            Node*   leftMost() const {
                const Node*   tmp = this;

                while (tmp->left) {
                    tmp = tmp->left;
                }
                return (const_cast<Node*>(tmp));
            }

            Node*   getPrevious() const {
                const Node*   previous = this;
                if (left) {
                    previous = left->rightMost();
                } else {
                    Node*   tmp = this->parent;
                    while (tmp && tmp->left == previous) {
                        previous = tmp;
                        tmp = tmp->parent;
                    }
                    if (tmp)
                        previous = tmp;
                    else
                        previous = NULL;
                }
                return (const_cast<Node*>(previous));
            }

            Node*   getNext() const {
                const Node*   next = this;
                if (this->right != NULL) {
                    next = right->leftMost();
                } else {
                    const Node*   tmp = this->parent;
                    while (tmp && tmp->right == next) {
                        next = tmp;
                        tmp = tmp->parent;
                    }
                    if (tmp)
                        next = tmp;
                    else
                        next = NULL;
                }
                return (const_cast<Node*>(next));
            }
    };

    typedef T                       value_type;
    typedef Compare                 value_compare;
    typedef value_type*             pointer;
    typedef const value_type*       const_pointer;
    typedef value_type&             reference;
    typedef const value_type&       const_reference;

    // typedef struct RBTNode          Node;

    struct const_iterator : public ft::iterator<std::bidirectional_iterator_tag, const T> {
        public:

            typedef typename ft::iterator<std::bidirectional_iterator_tag, const T>::iterator_category  iterator_category;
            typedef typename ft::iterator<std::bidirectional_iterator_tag, const T>::value_type         value_type;
            typedef typename ft::iterator<std::bidirectional_iterator_tag, const T>::pointer            pointer;
            typedef typename ft::iterator<std::bidirectional_iterator_tag, const T>::reference          reference;
            typedef typename ft::iterator<std::bidirectional_iterator_tag, const T>::difference_type    difference_type;

            const_iterator() : _ptr(NULL) {};

            const_iterator(const const_iterator & it) {
                *this = it;
            };

            const_iterator(const Node* ptr, const RedBlackTree *parent) : _ptr(ptr), _parent(parent) {};
            const_iterator &operator=(const_iterator const &other) {
                _ptr = other._ptr;
                _parent = other._parent;
                return (*this);
            }


            reference   operator*() { return _ptr->item; };
            pointer     operator->() { return &_ptr->item; };
            // Prefix increment
            const_iterator& operator++() { _ptr = (_ptr = _ptr->getNext()) ? _ptr : _parent->_end; return *this;}  
            // Postfix increment
            const_iterator operator++(int) { const_iterator tmp = *this; ++(*this); return tmp; }
            // Prefix decrement
            // const_iterator& operator--() { _ptr = _ptr->getPrevious(); return *this; }  
            const_iterator& operator--() { _ptr = _ptr == _parent->_end ? _parent->_root->rightMost() : _ptr->getPrevious();return *this;}  

            // Postfix decrement
            const_iterator operator--(int) { const_iterator tmp = *this; --(*this); return tmp; }


            bool    operator!=(const const_iterator & it) { return (_ptr != it._ptr); }
            bool    operator==(const const_iterator & it) { return (_ptr == it._ptr); }


        protected:
            const Node* _ptr;
            const RedBlackTree    *_parent;

    };
    struct iterator : public ft::iterator<std::bidirectional_iterator_tag, T> {

        public:

            typedef typename ft::iterator<std::bidirectional_iterator_tag, T>::iterator_category  iterator_category;
            typedef typename ft::iterator<std::bidirectional_iterator_tag, T>::value_type         value_type;
            typedef typename ft::iterator<std::bidirectional_iterator_tag, T>::pointer            pointer;
            typedef typename ft::iterator<std::bidirectional_iterator_tag, T>::reference          reference;
            typedef typename ft::iterator<std::bidirectional_iterator_tag, T>::difference_type    difference_type;

            iterator() : _ptr(NULL) {};

            iterator(const iterator & it) {
                *this = it;
            };

            iterator(Node* ptr, RedBlackTree * parent) : _ptr(ptr), _parent(parent) {};
            iterator &operator=(iterator const &other) {
                _ptr = other._ptr;
                _parent = other._parent;
                return (*this);
            }


            Node* get_node() { return (_ptr); };

            reference   operator*() { return _ptr->item; };
            pointer     operator->() { return &_ptr->item; };
            // Prefix increment
            iterator& operator++() { _ptr = (_ptr = _ptr->getNext()) ? _ptr : _parent->_end; return *this;}  

            // Postfix increment
            iterator operator++(int) { iterator tmp = *this; ++(*this); return tmp; }
            // Prefix decrement
            // iterator& operator--() { _ptr = _ptr->getPrevious(); return *this; }  
            iterator& operator--() { _ptr = _ptr == _parent->_end ? _parent->_root->rightMost() : _ptr->getPrevious();return *this;}  

            // Postfix decrement
            iterator operator--(int) { iterator tmp = *this; --(*this); return tmp; }

            bool    operator!=(const iterator & it) { return (_ptr != it._ptr); }
            bool    operator==(const iterator & it) { return (_ptr == it._ptr); }

            operator const_iterator () const { return const_iterator(static_cast<const Node*>(_ptr), static_cast<const RedBlackTree*>(_parent)) ; }

        private:
            Node* _ptr;
            RedBlackTree    *_parent;

    };

    struct const_reverse_iterator : public ft::iterator<std::bidirectional_iterator_tag, const T> {
        public:    

            typedef typename ft::iterator<std::bidirectional_iterator_tag, const T>::iterator_category  iterator_category;
            typedef typename ft::iterator<std::bidirectional_iterator_tag, const T>::value_type         value_type;
            typedef typename ft::iterator<std::bidirectional_iterator_tag, const T>::pointer            pointer;
            typedef typename ft::iterator<std::bidirectional_iterator_tag, const T>::reference          reference;
            typedef typename ft::iterator<std::bidirectional_iterator_tag, const T>::difference_type    difference_type;

            const_reverse_iterator() : _ptr(NULL) {};

            const_reverse_iterator(const const_reverse_iterator & it) {
                *this = it;
            };

            const_reverse_iterator (Node* ptr, const RedBlackTree *parent) : _ptr(ptr), _parent(parent) {};

            reference   operator*() { return _ptr == _parent->_end ? _parent->_root->rightMost()->item : _ptr->getPrevious()->item; };
            pointer     operator->() { return _ptr == _parent->_end ? _parent->_root->rightMost()->item : _ptr->getPrevious()->item; };
            // Prefix increment
            // const_reverse_iterator & operator++() { _ptr = _ptr->getPrevious(); return *this; }  
            const_reverse_iterator& operator++() { _ptr = _ptr == _parent->_end ? _parent->_root->rightMost() : _ptr->getPrevious();return *this;}  

            // Postfix increment
            const_reverse_iterator  operator++(int) { const_reverse_iterator  tmp = *this; ++(*this); return tmp; }
            // Prefix decrement
            // const_reverse_iterator & operator--() { _ptr = _ptr->getNext(); return *this; }  
            const_reverse_iterator & operator--() { _ptr = (_ptr = _ptr->getNext()) ? _ptr : _parent->_end; return *this;}  

            // Postfix decrement
            const_reverse_iterator  operator--(int) { const_reverse_iterator  tmp = *this; --(*this); return tmp; }

            bool    operator!=(const const_reverse_iterator & it) { return (_ptr != it._ptr); }
            bool    operator==(const const_reverse_iterator & it) { return (_ptr == it._ptr); }


        private:
            const Node* _ptr;
            const RedBlackTree    *_parent;

    };

    struct reverse_iterator : public ft::iterator<std::bidirectional_iterator_tag, T> {
        public:    

            typedef typename ft::iterator<std::bidirectional_iterator_tag, T>::iterator_category  iterator_category;
            typedef typename ft::iterator<std::bidirectional_iterator_tag, T>::value_type         value_type;
            typedef typename ft::iterator<std::bidirectional_iterator_tag, T>::pointer            pointer;
            typedef typename ft::iterator<std::bidirectional_iterator_tag, T>::reference          reference;
            typedef typename ft::iterator<std::bidirectional_iterator_tag, T>::difference_type    difference_type;

            reverse_iterator() : _ptr(NULL) {};

            reverse_iterator(const reverse_iterator & it) {
                *this = it;
            };

            reverse_iterator(Node* ptr, RedBlackTree *parent) : _ptr(ptr), _parent(parent) {};

            reference   operator*() { return _ptr == _parent->_end ? _parent->_root->rightMost()->item : _ptr->getPrevious()->item; };
            pointer     operator->() { return _ptr == _parent->_end ? _parent->_root->rightMost()->item : _ptr->getPrevious()->item; };
            // Prefix increment
            // reverse_iterator& operator++() { _ptr = _ptr->getPrevious(); return *this; }  
            reverse_iterator& operator++() { _ptr = _ptr == _parent->_end ? _parent->_root->rightMost() : _ptr->getPrevious();return *this;}  

            // Postfix increment
            reverse_iterator operator++(int) { reverse_iterator tmp = *this; ++(*this); return tmp; }
            // Prefix decrement
            // reverse_iterator& operator--() { _ptr = _ptr->getNext(); return *this; }  
            reverse_iterator & operator--() { _ptr = (_ptr = _ptr->getNext()) ? _ptr : _parent->_end; return *this;}  

            // Postfix decrement
            reverse_iterator operator--(int) { reverse_iterator tmp = *this; --(*this); return tmp; }

            operator const_reverse_iterator  () const { return const_reverse_iterator (_ptr, _parent) ; }

            bool    operator!=(const reverse_iterator & it) { return (_ptr != it._ptr); }
            bool    operator==(const reverse_iterator & it) { return (_ptr == it._ptr); }


        private:
            Node* _ptr;
            RedBlackTree    *_parent;
    };


    RedBlackTree() : _size(0) {
        _end = static_cast<Node*>(::operator new(sizeof(Node)));
        _root = _end;
    };

    RedBlackTree(const RedBlackTree & rbt) {
        *this = rbt;
    }

    ~RedBlackTree() {
        clear();
        delete _end;
    }

    RedBlackTree&   operator=(const RedBlackTree& x) {
        clear();
        copy(x._root);
        return (*this);
    }   
    const_iterator begin() const {
        if (_size == 0)
            return end();
        return (const_iterator(_root->leftMost(), this));
        // return (const_iterator(_root->leftMost(), this));
    }
    iterator begin() {
        if (_size == 0)
            return end();
        // return (iterator(_root->leftMost(), this));
        return (iterator(_root->leftMost(), this));

    }
    const_iterator end() const {
        return (const_iterator(_end, this));

        // return (const_iterator(_end, this));
    }
    iterator end() {
        return (iterator(_end, this));

        // return (iterator(_end, this));
    }
    const_reverse_iterator rbegin() const {
        return (const_reverse_iterator(_end, this));
    }
    const_reverse_iterator rend() const {
        return (const_reverse_iterator(_root->leftMost(), this));
    }
    reverse_iterator rbegin() {
        return (reverse_iterator(_end, this));
    }
    reverse_iterator rend() {
        return (reverse_iterator(_root->leftMost(), this));
    }

    void    copy(Node*  x) {
        if (x == NULL)
            return ;
    
        insert(x->item);
        copy(x->left);
        copy(x->right);

    }

    void clear() {
        deleteTree(_root);
        _root = _end;
        _size = 0;
    }

    struct Trunk
    {
        Trunk *prev;
        std::string str;
    
        Trunk(Trunk *prev, std::string str)
        {
            this->prev = prev;
            this->str = str;
        }
    };
    
    // Helper function to print branches of the binary tree
    void showTrunks(Trunk *p)
    {
        if (p == NULL)
            return;
    
        showTrunks(p->prev);
    
        std::cout << p->str;
    }
    void printTree(Node *root, Trunk *prev, bool isLeft)
    {
        if (_size == 0)
            return;
        if (root == NULL)
            root = _root;
    
        std::string prev_str = "    ";
        Trunk *trunk = new Trunk(prev, prev_str);
    
        if (root->right)
            printTree(root->right, trunk, true);
    
        if (!prev)
            trunk->str = "———";
        else if (isLeft)
        {
            trunk->str = ".———";
            prev_str = "    |";
        }
        else
        {
            trunk->str = ".———";
            prev->str = prev_str;
        }
    
        showTrunks(trunk);
        std::cout << (root->color == RED ? "\033[31m" : "\033[37m") << root->item << ":" << (root->parent ? root->parent->item.first : 0) << "\033[37m" << std::endl;  

        // std::cout << root->item << std::endl;
    
        if (prev)
            prev->str = prev_str;
        trunk->str = "    |";
    
        if (root->left)
            printTree(root->left, trunk, false);
    }

    void    printOrder() {
        Node* start = _root->leftMost();
        while (start) {
            std::cout << start->item << std::endl;
            start = start->getNext();
        }
    }

    void    printReverseOrder() {
        Node* start = _root->rightMost();
        while (start) {
            std::cout << start->item << std::endl;
            start = start->getPrevious();
        }
    }

    size_t max_size() const {
        return (std::numeric_limits<std::ptrdiff_t>::max() / sizeof(RedBlackTree));
    }


    // ft_containers Map hint insertion


    // iterator insert (iterator pos, const value_type& val);
    
    // If (pos == end)
    //     if (size > 0 && val > rightmost)
    //         insert at the end (after rightmost) // return
    //     else
    //         normal insertion // return
    // Else if (val < pos)
    //     before = pos - 1
    //     if (pos == leftmost)
    //         insert before leftmost // return
    //     else if (val > before)
    //         if (before->right == NULL)
    //             insert at right of ‘before’ // return
    //         else
    //             insert from left of pos // return
    //     else
    //         normal insertion // return
    // Else if (val > pos)
    //     after = pos + 1
    //     if (pos == rightmost)
    //         insert at the end (after rightmost) // return
    //     else if (v < after)
    //         if (pos->right == NULL)
    //             insert at right of pos // return
    //         else
    //             insert from left of ‘after’ // return
    //     else
    //         normal insertion // return
    // Else
    //     return iterator of pos

    iterator    insert(iterator pos, const value_type& val) {
        if (pos.get_node() == _end) {
            if (_size > 0 && _value_comp(_root->rightMost()->item, val))
                return insert(_root->rightMost(), val);
            else{
                return insert(val).first;
            }
        } else if (_value_comp(val, pos.get_node()->item)) {
            iterator    before = pos;
            if (pos.get_node() == _root->leftMost())
                return insert(_root->leftMost(), val);
            else if (_value_comp((--before).get_node()->item, val)) {
                if (before.get_node()->right == NULL)
                    return insert(before.get_node(), val);
                else
                    return insert(pos.get_node(), val);
            } else {
                return insert(val).first;
            }
        } else if (_value_comp(pos.get_node()->item, val)) {
            iterator    after = pos;
            if (pos.get_node() == _root->rightMost())
                return insert(_root->rightMost(), val);
            else if (_value_comp(val, (++after).get_node()->item)) {
                if (pos.get_node()->right == NULL)
                    return insert(pos.get_node(), val);
                else
                    return insert(after.get_node(), val);
            } else {
                return insert(val).first;
            }
        }
        return pos;
    }

    Pair<iterator, bool>    insert(const value_type& val) {
        Pair<iterator, bool> res;

        size_t  size = _size;
        res.first = insert(_root, val);
        res.second = size < _size;
        return (res);
    }
    
    // Node*    insert(const value_type& new_item) {
    //     return (insert(_root, new_item));
    // }

    // void    erase (iterator position) {
    //     e
    // }
    size_t    erase (const value_type & delete_item) {
        return erase(iterator(_root, this), delete_item);
    }


    size_t    erase(iterator pos, const value_type & delete_item) {
        Node* tmp = pos.get_node();
        size_t  size = 0;
        while (tmp)
        {
            if (_value_comp(delete_item, tmp->item)) {
                tmp = tmp->left;
            } else if (_value_comp(tmp->item, delete_item)) {
                tmp = tmp->right;
            } else {
                Node* p = tmp->parent;
                Node* replace = tmp;
                Color color = tmp->color;
                Color replacedColor = BLACK;
                if (tmp->left && tmp->right) {
                    Node* succ = tmp->right;
                    while (succ->left) {
                        succ = succ->left;
                    }
                    value_type val = succ->item;
                    // size += erase(succ->item);
                    if (succ->parent->right == succ)
                        succ->parent->right = succ->right;
                    else
                        succ->parent->left = succ->right;
                    if (succ->right)
                        succ->right->parent = succ->parent;
                    if (tmp != _root) {
                        if (tmp->parent->left == tmp)
                            tmp->parent->left = succ;
                        else 
                            tmp->parent->right = succ;
                    } else {
                        _root = succ;
                    }
                    replace = succ;
                    replacedColor = succ->color;
                    succ->parent = tmp->parent;
                    succ->left = tmp->left;
                    if (tmp->left)
                        tmp->left->parent = succ;
                    if (tmp->left)
                        tmp->left->parent = succ;
                    if (tmp->right)
                        tmp->right->parent = succ;
                    if (tmp->right != succ)
                        succ->right = tmp->right;
                    succ->color = tmp->color;
                    // if (tmp != _root) {
                    //     if (p->right == tmp)
                    //         p->right = succ;
                    //     else
                    //         p->left = succ;
                    //     c->parent = p;
                    //     replacedColor = c->color;
                    //     replace = c;
                    // } else {
                    //     _root = c;
                    //     c->parent = NULL;
                    // }
                    // c->color = BLACK;
                    delete tmp;
                    // replacedColor = succ->color;
                    // tmp->item = val;
                    // break;
                } else if (tmp->left || tmp->right) {
                    Node* c = tmp->left ? tmp->left : tmp->right;
                    if (tmp != _root) {
                        if (p->right == tmp)
                            p->right = c;
                        else
                            p->left = c;
                        c->parent = p;
                        replacedColor = c->color;
                        replace = c;
                    } else {
                        _root = c;
                        c->parent = NULL;
                    }
                    c->color = BLACK;
                    delete tmp;
                } else {
                    if (tmp == _root) {
                        _root = _end;
                    } else {
                        if (p) {
                            if (p->right == tmp) {
                                p->right = NULL;
                            }
                            else {
                                p->left = NULL;
                            }
                        }
                        replace = NULL;
                        replacedColor = BLACK;
                    }
                    delete tmp;
                }
                if (_size > 0 && color == BLACK && replacedColor == BLACK)
                    doubleBlackFix(replace, p);
                --_size;
                size++;
                break;
            }
        }
        return (size);
    }

    size_t  size() const {
        return (_size);
    }

    Node*   getRoot() const {
        return _root;
    }

    void    swap(RedBlackTree& x) {
        Node*       root = x._root;
        Node*       end = x._end;
        size_t      size = x._size;
        x._root = _root;
        x._end = _end;
        x._size = _size;
        _root = root;
        _end = end;
        _size = size;

    }

private:
    Node*   _root;
    Node*   _end;
    size_t  _size;
    value_compare _value_comp;

    void deleteTree(Node* node)  
    {  
        if (node == NULL || node == _end) return;  
    
        deleteTree(node->left);  
        deleteTree(node->right);  
        
        delete node; 
    }

    void    doubleBlackFix(Node* n, Node* p) {
        if (!p) // no parent means n is the root
            return;
        bool    isLeft = p->left == n;
        Node*   s = isLeft ? p->right : p->left;
        if (s && s->color == RED) {
            s->color = p->color;
            p->color = RED;
            if (p->left == n)
                leftRotate(p);
            else
                rightRotate(p);
            doubleBlackFix(n, p);
        } else {
            if ((!s->left || s->left->color == BLACK) && (!s->right || s->right->color == BLACK)) {
                s->color = RED;
                if (p->color == RED)
                    p->color = BLACK;
                else
                    doubleBlackFix(p, p->parent);
            } else if ((s->left && s->left->color == RED) || (s->right && s->right->color == RED)) {
                bool isChildRight = (s->right && s->right->color == RED);
                Node* redChild = isChildRight ? s->right : s->left;
                if ((isLeft && !isChildRight) || (!isLeft && isChildRight)) {
                    redChild->color = BLACK;
                    s->color = RED;
                    if (isLeft)
                        rightRotate(s);
                    else
                        leftRotate(s);
                }
                Color p_color = p->color;
                p->color = s->color;
                s->color = p_color;
                if (isLeft)
                    leftRotate(p);
                else
                    rightRotate(p);
                redChild->color = BLACK;
                
            }
        }
    }
    void    rightRotate(Node* a) {
        Node* p = a->parent;
        Node* b = a->left;
        a->left = b->right;
        if (b->right != NULL)
            b->right->parent = a;
        b->right = a;
        a->parent = b;
        b->parent = p;
        if (p != NULL) {
            if (p->left == a)
                p->left = b;
            else
                p->right = b;
        }
        if (a == _root) {
            _root = b;
        }
        // return b;
    }
    void    leftRotate(Node* a) {
        Node* p = a->parent;
        Node* b = a->right;
        a->right = b->left;
        if (b->left != NULL)
            b->left->parent = a;
        b->left = a;
        a->parent = b;
        b->parent = p;
        if (p != NULL) {
            if (p->left == a)
                p->left = b;
            else
                p->right = b;
        }
        if (a == _root) {
            _root = b;
        }

        // return b;
    }

    void    balance(Node* x) {
        if (x && x->color == RED && x->parent && x->parent->color == RED) {
            Node* p = x->parent; // parent
            if (p && p->parent) {
                Node* g = p->parent; // grandparent
                Node* u = (g->left == p) ? g->right : g->left; // uncle
                if (u && u->color == RED) {
                    p->color = BLACK;
                    u->color = BLACK;
                    if (g != _root) {
                        g->color = RED;
                        balance(g);
                    }
                } else {
                    if (g->left == p) {
                        if (p->left == x) {
                            rightRotate(g);
                            Color gc = g->color;
                            g->color = p->color;
                            p->color = gc;
                        } else {
                            leftRotate(p);
                            balance(p);
                        }
                    } else {
                        if (p->right == x) {
                            leftRotate(g);
                            Color gc = g->color;
                            g->color = p->color;
                            p->color = gc;
                        } else {
                            rightRotate(p);
                            balance(p);
                        }
                    }
                }
            } 
        }
    }


    iterator    insert(Node* pos, const value_type& new_item) {
        if (_size == 0) {
            _root = new Node(new_item);
            _root->color = BLACK;
            ++_size;

            return iterator(_root, this);
        }
        Node*    tmp = pos;
        while (tmp) {
            if (_value_comp(new_item, tmp->item)) {
                if (tmp->left) {
                    tmp = tmp->left;                    
                } else {
                    tmp->left = new Node(new_item);
                    tmp->left->parent = tmp;
                    tmp = tmp->left;
                    break;
                }
            } else if (_value_comp(tmp->item, new_item)) {
                if (tmp->right) {
                    tmp = tmp->right;                    
                } else {
                    tmp->right = new Node(new_item);
                    tmp->right->parent = tmp;
                    tmp = tmp->right;
                    break;
                }
            } else {
                return iterator(tmp, this);
            }
        }
        if (tmp) {
            balance(tmp);
            ++_size;
        }
        return (iterator(tmp, this));
    }

};


} // ft namespace


#endif
