#include <iostream>
#include "Deque.hpp"

int main() {
    int test = 1;
    if (test == 1) {
        ft::Deque<int> x;

        // x.resize(10, 1337);
        // x.resize(16, 1337);
        // x.resize(26, 1337);
        x.assign(14, 1337);
        ft::Deque<int>::iterator it = x.begin();
        it++;
        it++;
        x.insert(it, 7, 42);
        it = x.end();
        x.insert(it, 10, 88);
        it = x.end();
        x.insert(it, 19, 55);
        it = x.end();
        x.insert(it, 77);
        it = x.begin();
        it++;
        it++;
        x.erase(it);
        // // x.assign(26, 42);
        // for (int i = 0; it != x.rend(); ++it, ++i) {
        //     *it = i;
        // }
        // std::cout << (31 + BUFF_SIZE - 1) / BUFF_SIZE << std::endl;
        // std::cout << (32 + BUFF_SIZE - 1) / BUFF_SIZE << std::endl;
        // std::cout << (33 + BUFF_SIZE - 1) / BUFF_SIZE << std::endl;
        x.print();

        std::cout << "front: " << x.front() << std::endl;
        std::cout << "back: " << x.back() << std::endl;
    }
 
    return (0);
}