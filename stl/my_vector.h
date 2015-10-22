#ifndef MY_VECTOR
#define MY_VECTOR

template <typename T>
class my_vector {
private:
    T* _ptr = nullptr;
    int _size = 0;
public:
    const int size (void) { return _size; }
    my_vector (int size = 0, const T& initval = T()) {
        if (size > 0) {
            _size = size;
            _ptr = new T [size];
            for (int i = 0; i < size; i++) {
                _ptr[i] = initval;
            }
        }
    }
    ~my_vector() {
        if (_size > 0) {
            delete[] _ptr;
            _size = 0;
            _ptr = nullptr;
        }
    };
    using iterator = T*;
    using const_iterator = T* const;

    iterator& begin (void) { return _ptr; }
    const_iterator& begin (void) const { return _ptr; }

    iterator end (void) { return _ptr + _size; }
    const_iterator end (void) const { return _ptr + _size; }

    T& operator[] (int index) { return _ptr[index]; }
    const T& operator[] (int index) const { return _ptr[index]; }
};

#endif // MY_VECTOR
