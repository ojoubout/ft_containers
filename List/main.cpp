#include <list>
#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include "List.hpp"
class A {
public:
    // A() : _n(0) {};
    A(int n) : _n(n) {};
    int _n;
};

std::ostream & operator<<(std::ostream & out, A &a) {
    return (out << a._n);
}

bool is_even(const int i) {
    return ((i % 2) == 0);
}

struct is_near {
  bool operator() (double first, double second)
  { return (std::fabs(first-second)<5.0); }
};

bool mycomparison (double first, double second)
{ return ( int(first)<int(second) ); }


int main(void) {

    int test = 2;

    if (test == 1) {
        std::list<int> list;

        list.push_back(2);
        list.push_back(2);
        list.push_back(2);
        list.push_back(6);
        list.push_back(2);
        list.push_back(8);

        list.unique();
        std::list<int>::iterator it = list.begin();
        std::list<int>::iterator ite = list.end();
        while (it != ite) {
            std::cout << "value: " << *it << std::endl;
            it++;
        }
    } else if (test == 2) {
        ft::List<double> first, second;

        first.push_back (1.1);
        first.push_back (2.2);
        first.push_back (2.9);

        second.push_back (3.7);
        second.push_back (7.1);
        second.push_back (11.4);

        // first.sort();
        // second.sort();

        first.merge(second);

        // (second is now empty)

        second.push_back (7.0);

        first.merge(second,mycomparison);

        // ft::List<double>::iterator it = first.begin();
        ft::List<double>::iterator ite = first.end();
        std::cout << "first contains:";
        for (ft::List<double>::iterator it=first.begin(); it!=ite; ++it)
            std::cout << ' ' << *it;
        std::cout << '\n';

    } else if (test == 3) {

        ft::List<int> list;
        

        // int a = list.front();

        // std::cout << a << std::endl;

        list.push_back(1);
        list.push_back(2);
        list.push_back(3);
        list.push_back(4);
        list.push_back(5);
        list.push_front(0);

        // list.pop_front();

        int a = list.back();


        std::cout << ": " << a << std::endl;
        
        ft::List<int>::iterator it = list.begin();
        ft::List<int>::iterator ite = list.end();
        ft::List<int> list2;

        for (int i = 2; i < 200; i*=2) {
            list2.push_back(i);
        }

        ft::List<int>::iterator it22 = list2.begin();

        it22++;
        list.splice(list.begin(), list2, list2.end());

        it = list.begin();
        ite = list.end();
        while (it != ite) {
            std::cout << "value1: " << *it << std::endl;
            it++;
        }

        ft::List<int>::iterator it2 = list2.begin();
        ft::List<int>::iterator ite2 = list2.end();
        while (it2 != ite2) {
            std::cout << "value2: " << *it2 << std::endl;
            it2++;
        }

        // ++it;
        // // (*it) = 7;
        // std::cout << *it << std::endl;
        // --it;
        // std::cout << *it << std::endl;

        std::cout << list2.size() << " " << list.size() << std::endl;
        std::cout << std::boolalpha << list2.empty() << " " << list.empty() << std::endl;
        std::cout << list2.max_size() << std::endl;
    }
    
    return (0);
}