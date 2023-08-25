#ifndef _POSITION_HPP_
#define _POSITION_HPP_

#include <iostream>

struct Position {
    int x;
    int y;

    std::string to_string() const {
        return "(" + std::to_string(x) + ", " + std::to_string(y) + ")";
    }
};

#endif  // _POSITION_HPP_
