#include "functions.hpp"

#include <algorithm>
#include <iostream>
#include <random>
#include <vector>

int clamp(int n, int lower, int upper) {
    return std::max(lower, std::min(n, upper));
}

bool is_in(int n, int lower, int upper) {
    return n >= lower && n <= upper;
}

List<int> pick_random_points(int n, int lower, int upper) {
    srand(time(nullptr));

    List<int> points;

    for (int i = 0; i < n; i++) {
        points.push(rand() % (upper - lower) + lower);
    }

    return points;
}