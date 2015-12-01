
template <typename T>
struct C {
    A<T> _x;

    explicit C (int s) : _x(s) {
        cout << "C(int) ";
    }

    C (C&& rhs) : _x (move (rhs._x)) {
        cout << "C(C&&) ";
    }

    C& operator= (C&& rhs) {
        _x = std::move(rhs._x);
        cout << "=(C&&) ";
        return *this;
    }

    ~C() {
        cout << "~C() ";
    }
};
