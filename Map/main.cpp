#include <list>
#include <iostream>
#include <iomanip>
#include <map>
#include <cmath>
#include "RedBlackTree.hpp"

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


int main(void) {

    int test = 1;

    if (test == 1) {
        RedBlackTree<int> rbt;

        // rbt.insert(10);
        // rbt.insert(18);
        // rbt.insert(7);
        // rbt.insert(15);
        // rbt.insert(16);
        // rbt.insert(30);
        // rbt.insert(25);
        // rbt.insert(40);
        // rbt.insert(60);
        // rbt.insert(2);
        // rbt.insert(1);
        // rbt.insert(40);
        // rbt.insert(31);

        rbt.insert(10);
        rbt.insert(8);
        rbt.insert(16);
        rbt.insert(14);
        rbt.insert(12);
        rbt.insert(13);
        rbt.insert(9);
        // rbt.insert(10);
        // rbt.insert(10);
        // rbt.insert(4);

        // rbt.print2DUtil(NULL, 0);
        rbt.printTree(NULL , NULL, false);
        rbt.deletion(10);
        std::cout << "--------------------------" << std::endl;
        rbt.printTree(NULL , NULL, false);
        rbt.deletion(12);
        std::cout << "--------------------------" << std::endl;
        rbt.printTree(NULL , NULL, false);

    }
    return (0);
}