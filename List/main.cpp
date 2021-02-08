#include <list>
#include <iostream>
#include <iomanip>
#include "List.hpp"
class A {
public:
    // A() : _n(0) {};
    A(int n) : _n(n) {};
    int _n;
};

std::ostream & operator<<(std::ostream & out, A &a) {
    return (out << a._n);
}

int main(void) {

    std::list<int> list;

    // list.push_back(2);
    // list.pop_front();
    // int a = list.back();
    std::list<int>::iterator it = list.begin();

    std::cout << *it << std::endl;

    // ft::List<int> list;

    // int a = list.front();

    // std::cout << a << std::endl;

    // list.push_back(1);
    // list.push_back(2);
    // list.push_back(3);
    // list.push_back(4);
    // list.push_back(5);
    // list.push_front(0);

    // // list.pop_front();

    // int a = list.back();


    // std::cout << ": " << a << std::endl;
    
    // ft::List<int>::reverse_iterator it = list.rbegin();
    // ft::List<int>::reverse_iterator ite = list.rend();

    // while (it != ite) {
    //     std::cout << "value: " << *it << std::endl;
    //     it++;
    // }

    // ++it;
    // // (*it) = 7;
    // std::cout << *it << std::endl;
    // --it;
    // std::cout << *it << std::endl;

    std::cout << list.size() << std::endl;
    std::cout << std::boolalpha << list.empty() << std::endl;
    std::cout << list.max_size() << std::endl;

    return (0);
}