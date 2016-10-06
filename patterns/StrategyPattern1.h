#ifndef STRATEGY_PATTERN_H
#define STRATEGY_PATTERN_H

#include <string>

class Movie {
private:
    std::string _s;
    int _t;
    int _d;

public:
    static const int Childrens = 0;
    static const int NewRelease = 1;
    static const int Regular = 2;

    Movie (const std::string& s, int t, int d) :
        _s (s),
        _t (t),
        _d (d) { }

    int amount (void) {
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
