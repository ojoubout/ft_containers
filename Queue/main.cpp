#include "Queue.hpp"
#include "../tester/tester.hpp"

int main() {
    int test = 2;
    if (test == 1) {
        ft::Queue<int> s;

        s.push(4);
        s.push(5);
        s.push(2);
        s.push(9);

        while (!s.empty()) {
            std::cout << s.front() << " " << s.back() << std::endl;
            s.pop();
        }
    } else if (test == 2) {
        test_queue();
    }
        
}