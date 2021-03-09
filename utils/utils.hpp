#ifndef UTILS_HPP
# define UTILS_HPP

namespace ft {

// enable_if implementation

template<bool B, class U = void>
struct enable_if {};
 
template<class U>
struct enable_if<true, U> { typedef U type; };

// is_integral implementation

template<typename> struct is_integral {
    static const bool value = false;
};

template<> struct is_integral<bool> {static const bool value = true;};
template<> struct is_integral<char> {static const bool value = true;};
template<> struct is_integral<signed char> {static const bool value = true;};
template<> struct is_integral<short int> {static const bool value = true;};
template<> struct is_integral<int> {static const bool value = true;};
template<> struct is_integral<long int> {static const bool value = true;};
template<> struct is_integral<long long int> {static const bool value = true;};
template<> struct is_integral<unsigned char> {static const bool value = true;};
template<> struct is_integral<unsigned short int> {static const bool value = true;};
template<> struct is_integral<unsigned int> {static const bool value = true;};
template<> struct is_integral<unsigned long int> {static const bool value = true;};
template<> struct is_integral<unsigned long long int> {static const bool value = true;};

// is_same implementation

template<class T, class U>
struct is_same {static const bool value = false;};
 
template<class T>
struct is_same<T, T> {static const bool value = true;};

template <class T> struct less {
  bool operator() (const T& x, const T& y) const {return x<y;}
};

static class nullptr_t
{
    public:
        /*
        ** @brief For conversion to any type
        ** of null non-member pointer.
        */
        template<class T>
        operator T*() const { return (0); }

        /*
        ** @brief For conversion to any type of null
        ** member pointer.
        */
        template<class C, class T>
        operator T C::*() const { return (0); }

    private:
        
        /*
        ** @brief It's imposible to get an address of
        ** a nullptr.
        */
        void operator&() const;

} u_nullptr = {};

}

#endif
