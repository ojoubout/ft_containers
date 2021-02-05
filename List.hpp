#ifndef LIST_HPP
# define LIST_HPP
#include <list>
namespace ft {

template <typename T>
struct List_Node {
    T                   *content;
    struct List_Node    *next;
};

template <typename T>
class List {
private:
    struct List_Node   *head;
public:

    typedef T           value_type;
    typedef T&          reference;
    typedef const T&    const_reference;

    List();
    List(size_t *n, const value_type& val);
    template <class InputIterator>
    List (InputIterator first, InputIterator last);
    List(const List& x);
    ~List();

    List& operator= (const List& x);
    bool            empty() const;
    size_type       size() const;
    size_type       max_size() const;
    reference       front();
    const_reference front() const;
    reference       back();
    const_reference back() const;




}; // List class

} // ft namespace



#endif