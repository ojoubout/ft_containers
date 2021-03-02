#include <iostream>
#include "Deque.hpp"

int main() {
    int test = 1;
    if (test == 1) {
        ft::Deque<int> x;

        x.assign(16, 42);
        x.print();
    }
    return (0);
}