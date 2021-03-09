#include <iostream>
#include "Vector.hpp"
#include <vector>
// #include "../test/test.hpp"
// #include "../test/vector_test.hpp"
#include "../tester/tester.hpp"
#include <iostream>
#include <assert.h>
#include <iterator>
class A {
public:
    int n;
    A(int num) : n(num) {std::cout << "Constructure " << n << std::endl;};
    ~A() {std::cout << "Destructure " << n << std::endl;};
};

std::ostream &operator<<(std::ostream & out, const A & a) {
    return (out << a.n);
}
int main(int argc, char**) {
    int test = 2;
    if (test == 1) {
        int array[] = {5, 6, -4, 9, 1};
        std::vector<int> v(std::begin(array), std::end(array));
        std::cout << "size: " << v.size() << std::endl;
        std::vector<int>::iterator it = v.begin();
        for (it = v.begin(); it != v.end(); ++it) {
            std::cout << *it << std::endl;
        }

    } else if (test == 2) {
        test_vector();
    }

    if (argc != 1) {
        while (1);
    }
    
    return (0);
}