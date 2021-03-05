#ifndef DEQUE_HPP
# define DEQUE_HPP

#include <cstddef>
#include "../iterator_traits.hpp"
#include "deque_iterator.hpp"
#include "../utils.hpp"

namespace ft {

template < class T >
class Deque {
public:

    typedef T               value_type;
    typedef T&              reference;
    typedef const T&        const_reference;
    typedef T*              pointer;
    typedef T**             map_pointer;
    typedef const T*        const_pointer;
    typedef std::ptrdiff_t  difference_type;
    typedef size_t          size_type;

    typedef deque_iterator<value_type>                  iterator;
    typedef deque_iterator<const value_type>            const_iterator;
    typedef deque_reverse_iterator<value_type>          reverse_iterator;
    typedef deque_reverse_iterator<const value_type>    const_reverse_iterator;

    explicit Deque() {
        init();
    }

    explicit Deque (size_type n, const value_type& val = value_type());

    template <class InputIterator>
    Deque (InputIterator first, InputIterator last);

    Deque (const Deque& x) {
        *this = x;
    }

    ~Deque() {
        
    }

    Deque& operator= (const Deque& x);


    void print() {
        std::cout << "_map_size:        " << _map_size << std::endl;
        std::cout << "_last_chunk_size: " << _last_chunk_size << std::endl;
        std::cout << "size()            : " << size() << std::endl;
        for (size_type i = 0; i < _map_size; i++) {
            size_type max = (_last_chunk_size && i == _map_size - 1) ? _last_chunk_size : BUFF_SIZE;
            for (size_type j = 0; j < max; j++) {
                std::cout << _map[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }

    // Iterators:

    iterator    begin() {
        return (iterator(_map, 0));
    }

    iterator    end() {
        if (_last_chunk_size == 0)
            return (iterator(_map + _map_size, _last_chunk_size));
        return (iterator(_map + _map_size - 1, _last_chunk_size));
    }
    const_iterator    begin() const {
        return (const_iterator(_map, 0));
    }

    const_iterator    end() const {
        if (_last_chunk_size == 0)
            return (const_iterator(_map + _map_size, _last_chunk_size));
        return (const_iterator(_map + _map_size - 1, _last_chunk_size));
    }

    reverse_iterator    rend() {
        return (reverse_iterator(_map - 1, BUFF_SIZE));
    }

    reverse_iterator    rbegin() {
        if (_last_chunk_size == 0)
            return (reverse_iterator(_map + _map_size, _last_chunk_size));
        return (reverse_iterator(_map + _map_size - 1, _last_chunk_size));
    }
    const_reverse_iterator    rend() const {
        return (const_reverse_iterator(_map - 1, BUFF_SIZE));
    }

    const_reverse_iterator    rbegin() const {
        if (_last_chunk_size == 0)
            return (const_reverse_iterator(_map + _map_size, _last_chunk_size));
        return (const_reverse_iterator(_map + _map_size - 1, _last_chunk_size));
    }

    // Capacity:

    size_type size() const {
        return ((_map_size - 1) * BUFF_SIZE + _last_chunk_size);
    }

    size_type max_size() const {
        return (std::min((size_type) std::numeric_limits<difference_type>::max(),
                std::numeric_limits<size_type>::max() / (sizeof(value_type) * 2)));
    }

    // void resize (size_type n, value_type val = value_type()) {
    //     if (n > size()) {
    //         size_type   last_chunk_size = ((n % BUFF_SIZE) == 0 && n != 0) ? BUFF_SIZE : n % BUFF_SIZE ;
    //         size_type   map_size = last_chunk_size == BUFF_SIZE ? n / BUFF_SIZE : n / BUFF_SIZE + 1;
    //         map_pointer map = _map;
    //         if (map_size > _map_size)
    //             map = new pointer[map_size];
            
    //         if (_map_size != 0 && _map != map) {
    //             for (size_type i = 0; i < _map_size; i++) {
    //                 memcpy(map[i], _map[i], i == (_map_size - 1) ? _last_chunk_size : BUFF_SIZE);
    //                 free(_map[i]);
    //             }
    //             free(_map);
    //         }
    //         _map_size = _map_size - 1 + _last_chunk_size / BUFF_SIZE;
    //         _last_chunk_size = _last_chunk_size % BUFF_SIZE;
    //         for (size_type i = _map_size; i < map_size; i++) {
    //             map[i] = static_cast<pointer>(::operator new(sizeof(value_type) * BUFF_SIZE));
    //             size_type max_j = i == (map_size - 1) ? last_chunk_size : BUFF_SIZE;
    //             for (size_type j = _last_chunk_size; j < max_j; j++) {
    //                 map[i][j] = val;
    //             }
    //             _last_chunk_size = 0;
    //         }
    //         _map = map;
    //         _last_chunk_size = last_chunk_size;
    //         _map_size = map_size;

    //         // for (size_type i = 0; i < _map_size; i++) {
    //         //     _map[i] = static_cast<pointer>(::operator new(sizeof(value_type) * BUFF_SIZE));
    //         //     for (size_type j = 0; j < BUFF_SIZE && n > 0; j++, n--) {
    //         //         _map[i][j] = val;
    //         //     }
    //         // }

    //     }
    // }


    void resize (size_type n, value_type val = value_type()) {
        size_type   map_size = (n + BUFF_SIZE - 1) / BUFF_SIZE;
        size_type   last_chunk_size = ((n % BUFF_SIZE) == 0 && n != 0) ? BUFF_SIZE : n % BUFF_SIZE ;
        if (map_size == _map_size) {
            if (last_chunk_size < _last_chunk_size) {
                for (size_type i = last_chunk_size - 1; i < _last_chunk_size; i++) {
                    _map[_map_size - 1][i].~value_type();
                }
                _last_chunk_size = last_chunk_size;
            } else if (last_chunk_size > _last_chunk_size) {
                for (size_type i = _last_chunk_size; i < last_chunk_size; i++) {
                    _map[_map_size - 1][i] = val;
                }
                _last_chunk_size = last_chunk_size;
            }
        } else if (map_size > _map_size) {
            map_pointer map = new pointer[map_size];
            for (size_type i = 0; i < _map_size; i++) {
                map[i] = _map[i];
                if (i == _map_size - 1) {
                    for (size_type j = _last_chunk_size; j < BUFF_SIZE; j++) {
                        map[i][j] = val;
                    }
                }
            }
            for (size_type i = _map_size; i < map_size; i++) {
                map[i] = static_cast<pointer>(::operator new(sizeof(value_type) * BUFF_SIZE));
                for (size_type j = 0; j < BUFF_SIZE && n > 0; j++, n--) {
                    map[i][j] = val;
                }

            }
            free(_map);
            _map = map;
        } else if (map_size < _map_size) {
            for (size_type i = map_size; i < _map_size; i++) {
                for (size_type j = 0; j < BUFF_SIZE; j++) {
                    _map[i][j].~value_type();
                }
                free(_map[i]);
            }
            if (map_size > 0) {
                for (size_type j = last_chunk_size; j < _last_chunk_size; j++) {
                    _map[map_size - 1][j].~value_type();
                }
            }
        }
        _map_size = map_size;
        _last_chunk_size = last_chunk_size;
    }



    bool empty() const {
        return (_map_size == 0 && _last_chunk_size == BUFF_SIZE);
    }

    // Element Access:

    reference operator[] (size_type n) {
        size_type map_pos = n / BUFF_SIZE;
        size_type chunk_pos = n % BUFF_SIZE;
        return (_map[map_pos][chunk_pos]);
    }

    const_reference operator[] (size_type n) const {
        size_type map_pos = n / BUFF_SIZE;
        size_type chunk_pos = n % BUFF_SIZE;
        return (_map[map_pos][chunk_pos]);
    }

    reference at (size_type n) {
        if (n < size()) {
            return (*this)[n];
        }
        throw std::out_of_range("ft::Deque::at");
    }

    const_reference at (size_type n) const {
        if (n < size()) {
            return (*this)[n];
        }
        throw std::out_of_range("ft::Deque::at");
    }

    reference front() {
        return (*begin());
    }

    const_reference front() const {
        return (*begin());
    }

    reference back() {
        return (*rbegin());
    }

    const_reference back() const {
        return (*rbegin());
    }


    // Modifiers:

    template <class InputIterator>
    void assign (InputIterator first, InputIterator last,
    typename enable_if<!is_integral<InputIterator>::value, InputIterator>::type = 0) {
        clear();
        insert(begin(), first, last);
    }

    void assign (size_type n, const value_type& val) {
        clear();
        resize(n, val);
    }

    void push_back (const value_type& val) {
        insert(end(), val);
    }

    void push_front (const value_type& val) {
        insert(begin(), val);
    }

    iterator insert (iterator position, const value_type& val) {
        insert(position, 1, val);
        return (position);
    }

    void insert (iterator position, size_type n, const value_type& val) {
        difference_type curr_pos = position._curr - position._first;
        difference_type curr_chunk = position._node - _map;
        size_type pos = curr_chunk * BUFF_SIZE + curr_pos;
        size_type old_size = size();
        // size_type last_chunk_size = _last_chunk_size - 1;
        resize(old_size + n);
        // print();
        for (size_type i = size() - 1; i >= pos + n ; --i, --old_size) {
            // std::cout << "i= " << i << ", old_size - 1= " << old_size - 1 << std::endl;
            // std::cout << "at(i)= " << at(i) << ", at(old_size - 1)= " << at(old_size - 1) << std::endl;
            at(i) = at(old_size - 1);
        }
        for (size_type i = pos; i < pos + n; ++i) {
            at(i) = val;
        }
        // for (size_type i = _map_size - 1; i >= curr_chunk; --i, ) {
        //     for (size_type j = _last_chunk_size - 1; j > curr_pos; --j) {
        //         _map[i][j] = at()
        //     }
        // }
        // std::cout << "pos: " << pos << ", curr_pos: " << curr_pos << ", curr_chunk: " << curr_chunk << std::endl;
    }

    template <class InputIterator>
    void insert (iterator position, InputIterator first, InputIterator last,
    typename enable_if<!is_integral<InputIterator>::value, InputIterator>::type = 0) {
        while (first != last) {
            insert(position, 1, *(first++));
        }
    }

    iterator erase (iterator position) {
        difference_type curr_pos = position._curr - position._first;
        difference_type curr_chunk = position._node - _map;
        size_type pos = curr_chunk * BUFF_SIZE + curr_pos;

        value_type & item = at(pos);
        item.~value_type();
        for (size_type i = pos; i < size() - 1; ++i) {
            at(i) = at(i + 1);
        }
        resize(size() - 1);
        return (position);
    }

    iterator erase (iterator first, iterator last);

    void clear() {
        for (size_type i = 0; i < _map_size; ++i) {
            size_type max = (i == _map_size - 1) ? _last_chunk_size : BUFF_SIZE;
            for (size_type j = 0; j < max; ++j) {
                _map[i][j].~value_type();
            }
            free(_map[i]);
        }
        free(_map);
        init();
    }



private:
    
        map_pointer     _map;
        size_type       _map_size;
        size_type       _last_chunk_size;
        void    init() {
            _map = static_cast<map_pointer>(::operator new(0));;
            _map_size = 0;
            _last_chunk_size = BUFF_SIZE;
        }

        // size_type   capacity() {
        //     return(_map_size * );
        // }
};

} // ft namespace

#endif