#ifndef STRATEGY_PATTERN_H
#define STRATEGY_PATTERN_H

#include <string>

class Movie {
public:
    enum MovieType {
        Childrens,
        NewRelease,
        Regular
    };

private:
    std::string _s;
    MovieType _t;
    int _d;

public:
    Movie (const std::string& s, MovieType t, int d) :
        _s (s),
        _t (t),
        _d (d) { }

    int amount (void) const {
        int retval = 2;
        switch (_t) {
        case Childrens:
            if (_d > 3) retval += (2 * (_d - 3));
            break;
        case Regular:
            if (_d > 2) retval += (2 * (_d - 2));
            break;
        case NewRelease:
            retval = _d * 3;
            break;
        }
        return retval;
    }
};

#endif // STRATEGY_PATTERN_H
