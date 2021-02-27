#include <list>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <utility>
#include <map>
#include "RedBlackTree.hpp"
#include "Pair.hpp"
#include "Map.hpp"
#include "../test/test.hpp"
#include "../test/map_test.hpp"

class A {
public:
    int n;
    A(int num) : n(num) {std::cout << "Constructure " << n << std::endl;};
    ~A() {std::cout << "Destructure " << n << std::endl;};
};

std::ostream &operator<<(std::ostream & out, const A & a) {
    return (out << a.n);
}

bool comparaison (const double & first, const double & second)
{
  return ( first < second);
}

template <class T>
struct great {
    bool    operator()(const T& x, const T&y) {
        return (x > y);
    }
};

int main(void) {

    int test = 1;

    if (test == 1) {
        ft::Map<char, int > rbt;


        rbt.insert(ft::make_pair<char, int>('A', 10));
        rbt.insert(ft::make_pair<char, int>('B', 8));
        rbt.insert(ft::make_pair<char, int>('C', 16));
        rbt.insert(ft::make_pair<char, int>('D', 14));
        rbt.insert(ft::make_pair<char, int>('F', 12));
        rbt.insert(ft::make_pair<char, int>('H', 13));
        rbt.insert(ft::make_pair<char, int>('K', 9));
        rbt.insert(ft::make_pair<char, int>('P', 4));

        rbt.print();
        std::cout << rbt.size() <<  std::endl;
        ft::Map<char, int>::const_iterator it = rbt.begin();
        ft::Map<char, int>::const_iterator ite = rbt.end();
        while (it != ite) {
            std::cout << *it << std::endl;
            ++it;
        }

    } else if (test == 2) {
        std::pair<std::string, int> p("WHAT", 42);

        // p.first = "Hello";
        // p.second = 1337;
        std::cout << p.first << " " << p.second << std::endl;
    } else if (test == 3) {
        test_Map< ft::Map<char, int> >();

    }
    return (0);
}