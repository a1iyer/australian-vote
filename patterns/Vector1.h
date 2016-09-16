// Vector1.h
// aiyer 2016-09-16
// SARC-OOPL assignment on 2016-09-15; (incomplete) implementation of my_vector

#ifndef VECTOR1_H
#define VECTOR1_H

#include <algorithm>
#include <initializer_list>

template <typename T>
class my_vector {
    using iterator = T*;
    using const_iterator = const T*;
    using reference = T&;
    using const_reference = const T&;
    using value_type = T;
    using size_type = size_t;

private:
    T* _b = nullptr;
    T* _e = nullptr;

public:
    my_vector(size_type s = 0, const_reference t = T()) {
        _b = new T[s];
        _e = _b + s;
        std::fill(_b, _e, t);
    }

    // Funky new syntax
    my_vector(std::initializer_list<T> t) : my_vector(t.size()) {
        std::copy(t.begin(), t.end(), _b);
    }

    ~my_vector() { delete[] _b; }

    // To stop the compiler from complaining, define these as default
    my_vector(const my_vector&) = default;
    my_vector& operator=(const my_vector&) = default;

    // Two flavors each of begin and end
    iterator begin() { return _b; }
    const_iterator begin() const { return _b; }
    iterator end() { return _e; }
    const_iterator end() const { return _e; }

    // Two flavors of index operator
    const value_type operator[](size_type s) const { return _b[s]; }
    reference operator[](size_type s) { return _b[s]; } 

    // Size method
    size_type size() const { return _e - _b; }
};

#endif // VECTOR1_H
