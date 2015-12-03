#ifndef HANDLE_H
#define HANDLE_H

#include <utility>
#include <cassert>

template<typename T>
class Handle {
private:
    struct count {
        T* _p;
        int _c;
    };
    count * _q;
public:
    Handle (T* t) { 
        _q = new count;
        _q->_p = t;
        _q->_c = 1;
    }

    Handle (const Handle& h) {
        _q = h._q;
        ++(_q->_c);
    }

    ~Handle() {
        if (unique()) {
            delete _q->_p;
            delete _q;
        } else {
            --(_q->_c);
        }
    }

    bool unique() const { return _q->_c == 1; }

    int use_count() const { return _q->_c; }

    T* get() {
        T* retval = nullptr;
        if (unique()) {
            retval = _q->_p;
        } else {
            --(_q->_c);
            T* temp = _q->_p;
            _q = new count;
            _q->_c = 1;
            _q->_p = temp->clone();
            retval = _q->_p;
        }
        assert (retval != nullptr);
        return retval;
    }

    const T* get() const { return _q->_p; }

    Handle& operator= (Handle rhs) {
        std::swap (_q, rhs._q);
        return *this;
    }

    friend bool operator== (const Handle& lhs, const Handle& rhs) {
        return *(lhs.get()) == *(rhs.get());
    }
};

#endif // HANDLE_H
