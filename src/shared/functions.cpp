#include "functions.hpp"

#include <iostream>

int clamp(int n, int lower, int upper) {
    return std::max(lower, std::min(n, upper));
}

bool is_in(int n, int lower, int upper) {
    return n >= lower && n <= upper;
}
