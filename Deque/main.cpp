#include <iostream>
#include "Deque.hpp"
#include "../tester/tester.hpp"

int main() {
    int test = 2;
    if (test == 1) {
        std::deque<int> stl_default_deque;
        ft::Deque<int> ft_default_deque;

        // fs.open("./tester/deques_output/constructor_default", std::fstream::in | std::fstream::out | std::fstream::trunc);
        // std::cout << ((printDequeAttributes(fs, stl_default_deque, ft_default_deque) == true) ? "[OK]" : "[NOP]");

        // fs << "\nCode executed:\n";
        // fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        // fs << "ft::Deque<int> ft_default_deque;\n";
        // fs << "\nCompared with:\n";
        // fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        // fs << "std::deque<int> stl_default_deque;\n";
        // fs.close();
    } else if (test == 2) {
        test_deque();
    }
 
    return (0);
}