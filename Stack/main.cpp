#include "Stack.hpp"
#include "../tester/tester.hpp"

int main() {
    int test = 2;
    if (test == 1) {
        ft::Stack<int> s;

        s.push(4);
        s.push(5);
        s.push(2);
        s.push(9);

        ft::Stack<int> s2(s);
        std::cout << s.empty() << std::endl;
        std::cout << s.size() << std::endl;
        std::cout << s.top() << std::endl;
        std::cout << (s2 == s) << std::endl;
        std::cout << (s2 != s) << std::endl;
        std::cout << (s2 < s) << std::endl;
        std::cout << (s2 <= s) << std::endl;
        std::cout << (s2 > s) << std::endl;
        std::cout << (s2 >= s) << std::endl;
        s.pop();
    } else if (test == 2) {
        test_stack();
    }
        
}