
#ifndef Vector_h
#define Vector_h

#include <algorithm>
#include <cstddef>
#include <memory>
#include <initializer_list>
#include <stdexcept>
#include <utility>

using namespace std::rel_ops;

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

    // The following four functions should go away if std::rel_ops worked, but
    // for some reason it doesn't work.
    friend bool operator!= (const my_vector& lhs, const my_vector& rhs) {
        return !(lhs == rhs);
    }

    friend bool operator <= (const my_vector& lhs, const my_vector& rhs) {
        return !(rhs < lhs);
    }

    friend bool operator > (const my_vector& lhs, const my_vector& rhs) {
        return (rhs < lhs);
    }

    friend bool operator >= (const my_vector& lhs, const my_vector& rhs) {
        return !(lhs < rhs);
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

    private:
        allocator_type _a;
        pointer _b;
        pointer _e;

    public:
        explicit my_vector (size_type s = 0,
                            const_reference v = T(),
                            const allocator_type& a = allocator_type()) :
                _a (a),
                _b ((s == 0) ? nullptr : _a.allocate(s)),
                _e ((s == 0) ? nullptr : _b + s) {
            for (auto i = _b; i != _e; i++) _a.construct(i, v);
        }

        my_vector (const my_vector& rhs) :
                _a (rhs._a),
                _b (rhs.size() == 0 ? nullptr : _a.allocate(rhs.size())),
                _e (rhs.size() == 0 ? nullptr : _b + rhs.size()) {
            for (auto i = 0; i < rhs.size(); i++) _a.construct(_b+i, rhs[i]);
        }

        my_vector& operator = (const my_vector& rhs) {
            my_vector that(rhs);
            std::swap(_a, that._a);
            std::swap(_b, that._b);
            std::swap(_e, that._e);
            return *this;
        }

        ~my_vector () { _a.deallocate(_b, size()); }

        my_vector(std::initializer_list<T> t) : my_vector(t.size()) {
            std::copy(t.begin(), t.end(), _b);
        }

        // Four de-reference operators
        reference operator [] (size_type i) { return _b[i]; }

        const_reference operator [] (size_type i) const {
            return (*const_cast<my_vector*>(this))[i];
        }

        reference at (size_type i) {
            if (i >= size()) throw std::out_of_range("Out");
            return _b[i];
        }

        const_reference at (size_type i) const {
            return (*const_cast<my_vector*>(this)).at(i);
        }

        // begin, end, size
        iterator begin () { return _b; }
        const_iterator begin () const { return const_cast<my_vector*>(this)->begin(); }
        iterator end () { return _e; }
        const_iterator end () const { return const_cast<my_vector*>(this)->end(); }
        size_type size () const { return _e - _b; }
};

#endif // Vector_h
