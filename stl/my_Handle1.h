#ifndef HANDLE_H
#define HANDLE_H

#include <utility>

template<typename T>
class Handle {
private:
    T* _t = nullptr;
public:
    Handle (T* t = nullptr) : _t (t) { }
    Handle (const Handle& h) {
        if (h.get() != nullptr) _t = h.get()->clone();
        else _t = nullptr;
    }
    ~Handle() { delete _t; }

    T* get() { return _t; }
    const T* get() const { return _t; }

    Handle& operator= (Handle rhs) {
        std::swap (_t, rhs._t);
        return *this;
    }

    friend bool operator== (const Handle& lhs, const Handle& rhs) {
        if (lhs.get() == nullptr && rhs.get() == nullptr) return true;
        else if (lhs.get() == nullptr || rhs.get() == nullptr) return false;
        else return *(lhs.get()) == *(rhs.get());
    }
};

#endif // HANDLE_H
