#include <list>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <utility>
#include <map>
#include "RedBlackTree.hpp"
#include "../Pair.hpp"
#include "Map.hpp"
// #include "../test/test.hpp"
// #include "../test/map_test.hpp"
#include "../tester/tester.hpp"

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

    int test = 4;

    if (test == 1) {
        ft::Map<int, int > mp;

		mp.insert(ft::make_pair(5, 5));
		mp.insert(ft::make_pair(6, 6));
		mp.insert(ft::make_pair(7, 7));
		mp.insert(ft::make_pair(8, 8));
		mp.insert(ft::make_pair(9, 9));
		mp.insert(ft::make_pair(10, 10));
		mp.insert(ft::make_pair(11, 11));
        mp.print();

		// mp.insert(mp.begin(), ft::make_pair(5, 42));
		// mp.insert(mp.begin(), ft::make_pair(6, 43));
		// mp.insert(mp.begin(), ft::make_pair(4, 44));
		// mp.insert(--mp.end(), ft::make_pair(3, 45));
		// mp.insert(--mp.end(), ft::make_pair(7, 46));

    	ft::Map<int, int>::const_iterator it;
        for (it = mp.begin(); it != mp.end(); ++it) {
            std::cout << *it << std::endl;
        }

        std::cout << mp.max_size() <<  std::endl;
        
        // ft::Map<int, int>::iterator it = mp.begin();
        // ft::Map<int, int>::iterator ite = mp.end();
        // while (it != ite) {
        //     std::cout << *it << std::endl;
        //     ++it;
        // }
        if (ft::is_same<ft::Map<int, int>::iterator::iterator_category, std::random_access_iterator_tag>::value)
            std::cout << "YES" << std::endl;

    } else if (test == 2) {
        std::pair<std::string, int> p("WHAT", 42);

        // p.first = "Hello";
        // p.second = 1337;
        std::cout << p.first << " " << p.second << std::endl;
    } else if (test == 3) {
        // test_Map< ft::Map<char, int> >();
        
    } else if (test == 4) {
        test_map();
        // while (1);
    }
    return (0);
}