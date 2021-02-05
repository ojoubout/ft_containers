#include <list>
#include <iostream>

class A {
public:
    A(int n) : _n(n) {};
    int _n;
};

std::ostream & operator<<(std::ostream & out, A &a) {
    return (out << a._n);
}

int main(void) {
    std::list<A *> l;


    A *a = new A(4);
    std::cout << "A " << a << std::endl;
    l.push_back(a);
    std::cout << *l.begin() << std::endl;
    a = 9;
    std::cout << "A " << a << std::endl;
    std::cout << *l.begin() << std::endl;
    return (0);
}