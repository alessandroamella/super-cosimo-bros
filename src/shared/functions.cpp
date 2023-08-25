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

List<int> pick_random_points(int n, int lower, int upper, int min_distance) {
    srand(time(nullptr));

    List<int> points;

    while (points.length() < n) {
        int new_point = rand() % (upper - lower) + lower;
        bool is_far_enough = true;

        for (int i = 0; i < points.length(); i++) {
            if (abs(new_point - points.at(i)) < min_distance) {
                is_far_enough = false;
                break;
            }
        }

        if (is_far_enough) {
            points.push(new_point);
        }
    }

    return points;
}