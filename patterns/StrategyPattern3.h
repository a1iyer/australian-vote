#ifndef STRATEGY_PATTERN_H
#define STRATEGY_PATTERN_H

#include <string>

class Movie {
protected:
    enum MovieType {
        Childrens,
        NewRelease,
        Regular
    };

    std::string _s;
    MovieType _t;
    int _d;

public:
    Movie (const std::string& s, MovieType t, int d) :
        _s (s),
        _t (t),
        _d (d) { }

    virtual int amount (void) = 0;
};

class ChildrensMovie : Movie {
public:
    ChildrensMovie (const std::string& s, int d) :
        Movie (s, Movie::Childrens, d) { }

    virtual int amount (void) {
        int retval = 2;
        if (_d > 3) retval += (2 * (_d - 3));
        return retval;
    }
};

class RegularMovie : Movie {
public:
    RegularMovie (const std::string& s, int d) :
        Movie (s, Movie::Regular, d) { }

    virtual int amount (void) {
        int retval = 2;
        if (_d > 2) retval += (2 * (_d - 2));
        return retval;
    }
};

class NewReleaseMovie : Movie {
public:
    NewReleaseMovie (const std::string& s, int d) :
        Movie (s, Movie::NewRelease, d) { }

    virtual int amount (void) {
        return _d * 3;
    }
};

#endif // STRATEGY_PATTERN_H
