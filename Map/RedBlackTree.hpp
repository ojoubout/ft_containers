#ifndef REDBLACKTREE_HPP
# define REDBLACKTREE_HPP

#include <string>
template <typename T>
class RedBlackTree {
public:
    enum Color{RED, BLACK};
    struct RBTNode
    {
        public:
            T               item;
            Color           color;
            struct RBTNode *left, *right, *parent;
            RBTNode(const T &val) : item(val), color(RED), left(NULL), right(NULL), parent(NULL) {};
    };

    typedef T                       value_type;
    typedef struct RBTNode          Node;
    RedBlackTree() : _root(NULL) {};


    RedBlackTree&   operator=(const RedBlackTree& x) {
        clear();
    }

    void clear() {
        deleteTree(_root);
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
        std::cout << (root->color == RED ? "\033[31m" : "\033[37m") << root->item << ":" << (root->parent ? root->parent->item : 0) << "\033[37m" << std::endl;  

        // std::cout << root->item << std::endl;
    
        if (prev)
            prev->str = prev_str;
        trunk->str = "    |";
    
        if (root->left)
            printTree(root->left, trunk, false);
    }



    Node*    insert(const value_type& new_item) {
        if (_root == NULL) {
            _root = new Node(new_item);
            _root->color = BLACK;
            std::cout << "Insert Root: " << _root->item << std::endl;
            return _root;
        }
        Node*    tmp = _root;
        while (tmp) {
            if (tmp->item > new_item) {
                if (tmp->left) {
                    tmp = tmp->left;                    
                } else {
                    tmp->left = new Node(new_item);
                    tmp->left->parent = tmp;
                    tmp = tmp->left;
                    std::cout << "Insert Left: " << tmp->item << std::endl;
                    break;
                }
            } else if (tmp->item < new_item) {
                if (tmp->right) {
                    tmp = tmp->right;                    
                } else {
                    tmp->right = new Node(new_item);
                    tmp->right->parent = tmp;
                    tmp = tmp->right;
                    std::cout << "Insert Right: " << tmp->item << std::endl;
                    break;
                }
            } else {
                tmp = NULL;
            }
        }
        if (tmp) {
            balance(tmp);
            ++_size;
        }
        return (tmp);
    }


    void    deletion(value_type delete_item) {
        Node* tmp = _root;
        while (tmp)
        {
            if (tmp->item > delete_item) {
                tmp = tmp->left;
            } else if (tmp->item < delete_item) {
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
                    deletion(succ->item);
                    // replacedColor = succ->color;
                    tmp->item = val;
                    break;
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
                        c->color = BLACK;
                    } else {
                        _root = c;
                    }
                    delete tmp;
                } else {
                    if (tmp == _root) {
                        _root = NULL;
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
                if (color == BLACK && replacedColor == BLACK)
                    doubleBlackFix(replace, p);
                --_size;
                break;
            }
        }
    }

    size_t  size() const {
        return (_size);
    }

private:
    Node*    _root;
    size_t  _size;

    void deleteTree(Node* node)  
    {  
        if (node == NULL) return;  
    
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
                bool isChildLeft = (s->left && s->left->color == RED);
                Node* redChild = isChildLeft ? s->left : s->right;
                if ((isLeft && isChildLeft) || (!isLeft && !isChildLeft)) {
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
        // std::cout << "TryBalance: " << x->item << std::endl;
        if (x && x->parent && x->parent->color == RED) {
            // std::cout << "Balance: " << x->item << std::endl;
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
};

#endif