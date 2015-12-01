#ifndef HANDLE_H
#define HANDLE_H

#include <utility>

template<typename T>
class Handle {
private:
    T* _t = nullptr;

protected:
    T* get() { return _t; }
    const T* get() const { return _t; }

public:
    Handle (T* t = nullptr) : _t (t) { }
    Handle (const Handle& h) {
        if (h.get() != nullptr) _t = h.get()->clone();
        else _t = nullptr;
    }
    ~Handle() { delete _t; }

    Handle& operator= (Handle rhs) {
        std::swap (_t, rhs._t);
        return *this;
    }

    friend bool operator== (const Handle& lhs, const Handle& rhs) {
        if (lhs.get() == nullptr && rhs.get() == nullptr) return true;
        else if (lhs.get() == nullptr || rhs.get() == nullptr) return false;
        else return *(lhs.get()) == *(rhs.get());
    }

    const AbstractShape& operator* () const {
        return *_t;
    }

    AbstractShape& operator* () {
        return *_t;
    }

    AbstractShape* operator-> () {
        return _t;
    }

    const AbstractShape* operator-> () const {
        return _t;
    }
};

#endif // HANDLE_H
