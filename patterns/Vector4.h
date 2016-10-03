// Vector4.h
// aiyer, 2016-09-29 C++ OOPL class assignment. Based on Glenn's Vector2.h.

#ifndef VECTOR4_H
#define VECTOR4_H

#include <algorithm>
#include <cstddef>
#include <memory>
#include <initializer_list>
#include <stdexcept>
#include <utility>

using std::rel_ops::operator!=;
using std::rel_ops::operator<=;
using std::rel_ops::operator>;
using std::rel_ops::operator>=;

template <typename T, typename A = std::allocator<T>>
class my_vector {
    friend bool operator == (const my_vector& lhs, const my_vector& rhs) {
        return (lhs.size() == rhs.size()) && std::equal(lhs.begin(), lhs.end(), rhs.begin());
    }
   
    friend bool operator < (const my_vector& lhs, const my_vector& rhs) {
        if (lhs.size() < rhs.size()) return true;
        for (auto i = 0; i < rhs.size(); i++) if (lhs[i] < rhs[i]) return true;
        return false;
    }

    public:
        using value_type      = T;

        using size_type       = std::size_t;
        using difference_type = std::ptrdiff_t;

        using       pointer   =       value_type*;
        using const_pointer   = const value_type*;

        using       reference =       value_type&;
        using const_reference = const value_type&;

        using       iterator  =       pointer;
        using const_iterator  = const_pointer;

        using allocator_type  = A;

    // The ordering of these member variables is very important. If _a is
    // declared after _b and _e, then gcc-4.8 generates warnings for the
    // constructors' initialization order.
    private:
        allocator_type _a;
        pointer _b;
        pointer _e;

    public:
        // The explicit keyword here keeps this constructor from being an
        // implicit type converter.
        explicit my_vector(size_type s = 0,
                           const_reference v = T(),
                           const allocator_type& a = allocator_type()) :
                _a (a),
                _b ((s == 0) ? nullptr : _a.allocate(s)),
                _e ((s == 0) ? nullptr : _b + s) {
            for (auto i = _b; i != _e; i++) _a.construct(i, v);
        }

        // Copy constructor
        my_vector(const my_vector& rhs) :
                _a (rhs._a),
                _b (rhs.size() == 0 ? nullptr : _a.allocate(rhs.size())),
                _e (rhs.size() == 0 ? nullptr : _b + rhs.size()) {
            for (auto i = 0; i < rhs.size(); i++) _a.construct(_b+i, rhs[i]);
        }

        // Move constructor; note the funny && syntax
        my_vector(my_vector&& rhs) :
                _a (rhs._a),
                _b (rhs._b),
                _e (rhs._e) {
            rhs._b = nullptr;
            rhs._e = nullptr;
        }

        // Copy assignment
        my_vector& operator=(const my_vector& rhs) {
            my_vector that(rhs);
            std::swap(_a, that._a);
            std::swap(_b, that._b);
            std::swap(_e, that._e);
            return *this;
        }

        // Move assignment; note the funny && syntax
        my_vector& operator=(my_vector&& rhs) {
            for (auto i = _b; i < _e; i++) _a.destroy(i);
            _a.deallocate(_b, size());
            _a = rhs._a;
            _b = rhs._b;
            _e = rhs._e;
            rhs._b = nullptr;
            rhs._e = nullptr;
            return *this;
        }

        ~my_vector() {
            for (auto i = _b; i < _e; i++) _a.destroy(i);
            _a.deallocate(_b, size());
        }

        // The initializer-list constructor first calls the simple constructor
        // with the size argument, then invokes std::copy.
        my_vector(std::initializer_list<T> t) : my_vector(t.size()) {
            std::copy(t.begin(), t.end(), _b);
        }

        // Four de-reference operators; two of them just call the other two with
        // modified const-ness.
        reference operator[](size_type i) { return _b[i]; }

        const_reference operator[](size_type i) const {
            return (*const_cast<my_vector*>(this))[i];
        }

        reference at(size_type i) {
            if (i >= size()) throw std::out_of_range("Out");
            return _b[i];
        }

        const_reference at(size_type i) const {
            return (*const_cast<my_vector*>(this)).at(i);
        }

        // begin() and end() variants, and size()
        iterator begin() { return _b; }
        const_iterator begin() const { return const_cast<my_vector*>(this)->begin(); }
        iterator end() { return _e; }
        const_iterator end() const { return const_cast<my_vector*>(this)->end(); }
        size_type size() const { return _e - _b; }
};

#endif // VECTOR4_H
