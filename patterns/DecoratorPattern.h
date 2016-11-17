#ifndef DECORATOR_PATTERN_H
#define DECORATOR_PATTERN_H

#include <map>
#include <iostream>

#define DEBUG true

template<typename F>
class cache {
public:
    using argument_type = typename F::argument_type;
    using result_type = typename F::result_type;

private:
    F _f;
    std::map <argument_type, result_type> _m;

public:

    cache (F f) : _f (f) { }

    result_type operator() (argument_type x) {
        result_type retval;
        auto search = _m.find (x);
        if (search != _m.end()) {
            if (DEBUG) std::cout << "Found " << x << " in the cache; value ";
            retval = search->second;
            if (DEBUG) std::cout << retval << "\n";
        } else {
            if (DEBUG) std::cout << "Not found " << x << " in the cache, adding ";
            retval = _f (x);
            if (DEBUG) std::cout << retval << "\n";
            _m[x] = retval;
        }
        return retval;
    }
};

#endif // DECORATOR_PATTERN_H
