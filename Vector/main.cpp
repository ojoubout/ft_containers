#include <iostream>
#include "Vector.hpp"
#include <vector>
#include "../test/test.hpp"
#include "../test/vector_test.hpp"
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
    int test = 3;
    if (test == 1) {
        std::vector<A> v;
        // v.reserve(180000);
        // std::vector<int>::iterator it = v.begin();
        
        v.push_back(5);
        v.push_back(3);
        v.push_back(2);
        // v.clear();

        std::cout << "f: " << v[0] << std::endl;
        std::cout << "s: " << v.size() << std::endl;    
        std::cout << "c: " << v.capacity() << std::endl;    

    } else if (test == 2) {
		ft::Vector<int> vec;
			assert(vec.size() == 0);

		vec.insert(vec.begin(), 5);
        vec.print_list();
		// display_container("[5]:", vec);
			assert(vec.front() == 5);
			assert(vec.back() == 5);
			assert(vec.size() == 1);

		vec.insert(vec.begin(), 2, 42);
        vec.print_list();

        ft::Vector<int> vec2;
			assert(vec2.size() == 0);

		vec2.insert(vec2.begin(), vec.begin(), vec.end());
        vec2.print_list();
		// display_container("vec2[42, 42, 5]:", vec2);
		// 	assert(vec2.front() == 42);
		// 	assert(vec2.back() == 5);
		// 	assert(vec2.size() == 3);

		// vec2.insert(vec2.end(), vec.begin(), vec.end());

		// display_container("vec[42, 42, 5]:", vec);        // v.clear();
        std::cout << "f: " << vec[0] << std::endl;
        std::cout << "s: " << vec.size() << std::endl;    
        std::cout << "c: " << vec.capacity() << std::endl;    
    } else if (test == 3) {
        test_Vector< ft::Vector<int> >();
    }

    if (argc != 1) {
        while (1);
    }
    
    return (0);
}