#include <iostream>
#include "Vector.hpp"
#include <vector>

class A {
public:
    int n;
    A(int num) : n(num) {};
};

std::ostream &operator<<(std::ostream & out, const A & a) {
    return (out << a.n);
}
int main(int argc, char**) {
    int test = 2;
    if (test == 1) {
        std::vector<A> v;

        v.push_back(8);
        v.push_back(7);
        v.push_back(6);

        std::vector<A> v1(v);
        v.clear();
        std::cout << v1[0] << std::endl;

    } else if (test == 2) {
        ft::Vector<A> v;

        // std::vector<int>::iterator it = v.begin();
        
        v.push_back(5);
        v.push_back(3);
        v.push_back(2);
        
        // ft::Vector<A> v2(v);
        // v.insert(v.begin(), 2);
        // v.insert(v.begin(), 4);
        // v.insert(v.end(), 8);
        // ft::Vector<int>::iterator it = v.begin();
        // ft::Vector<int>::iterator ite = v.end();
        // v.print_list();
        // v.assign(v2.begin(), v2.end());
        // v.pop_back();
        // v.pop_back();
        v.print_list();
        // v.clear();
        // v2.print_list();
        std::cout << "f: " << v[0] << std::endl;
        std::cout << "s: " << v.size() << std::endl;    
        std::cout << "c: " << v.capacity() << std::endl;    
    }

    if (argc != 1) {
        while (1);
    }
    
    return (0);
}