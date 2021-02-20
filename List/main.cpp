#include <list>
#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include "List.hpp"
#include "../test/test.hpp"
#include "../test/list_test.hpp"
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

template <typename T>
void print_list(const ft::List<T> &list) {
    typename ft::List<T>::const_iterator it = list.begin();
    typename ft::List<T>::const_iterator ite = list.end();
    while (it != ite) {
        std::cout << "value: " << *it << std::endl;
        it++;
    }
}

bool comparaison (const double & first, const double & second)
{
  return ( first < second);
}


int main(void) {

    int test = 4;

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

        first.push_back (7.1);
        first.push_back (5.5);
        first.push_back (9.9);
        first.push_back (2.0);
        first.push_back (1.1);
        first.push_back (9.2);
        first.push_back (5.0);
        first.push_back (4.9);
        first.print_list();
        first.reverse();
        first.print_list();

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
    } else if (test == 4) {
        // std::cout << "HELLO" << std::endl;
        test_List<ft::List<double>, double>();
    } else if (test == 5) {
        // double mydoubles[]={ 12.15,  2.72, 73.0,  12.77, 12.7,  3.14,
                    //    12.77, 73.35, 72.25, 15.3,  72.25 };
        ft::List<double> mylist;
        mylist.push_back(12.15);
        mylist.push_back(2.72);
        mylist.push_back(73.0);
        mylist.push_back(12.77);
        mylist.push_back(12.7);
        mylist.push_back(3.14);
        mylist.push_back(12.77);
        mylist.push_back(12.15);
        mylist.push_back(73.35);
        mylist.push_back(72.25);
        mylist.push_back(15.3);
        mylist.push_back(72.25);
        
        mylist.sort();             //  2.72,  3.14, 12.15, 12.77, 12.77,
                                    // 15.3,  72.25, 72.25, 73.0,  73.35

        //   mylist.unique();           //  2.72,  3.14, 12.15, 12.77
                                    // 15.3,  72.25, 73.0,  73.35

        mylist.unique (same_integral_part);  //  2.72,  3.14, 12.15
                                            // 15.3,  72.25, 73.0

        //   mylist.unique (is_near());           //  2.72, 12.15, 72.25

        std::cout << "mylist contains:";
        for (ft::List<double>::iterator it=mylist.begin(); it!=mylist.end(); ++it)
            std::cout << ' ' << *it;
        std::cout << '\n';
    }
    
    return (0);
}