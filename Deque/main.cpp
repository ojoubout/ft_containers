#include <iostream>
#include "Deque.hpp"
#include "../tester/tester.hpp"

int main() {
    int test = 2;
    if (test == 1) {
        ft::Deque<int> x;

        ft::Deque<int>::iterator it;
        for (it = x.begin(); it != x.end(); ++it) {
            std::cout << "ENTER: " << *it << std::endl;
        }

        // std::cout << "front: " << x.front() << std::endl;
        // std::cout << "back: " << x.back() << std::endl;
    } else if (test == 2) {
        test_deque();
    }
 
    return (0);
}