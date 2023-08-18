#include "functions.hpp"

#include <iostream>

int clamp(int n, int lower, int upper) {
    return std::max(lower, std::min(n, upper));
}