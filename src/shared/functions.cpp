#include "functions.hpp"

#include <algorithm>
#include <iostream>
#include <random>
#include <vector>

#include "../coin/coin.hpp"
#include "../gun/gun.hpp"
#include "../heart/heart.hpp"
#include "../mushroom/mushroom.hpp"
#include "../star/star.hpp"

int clamp(int n, int lower, int upper) {
    return std::max(lower, std::min(n, upper));
}

bool is_in(int n, int lower, int upper) {
    return n >= lower && n <= upper;
}

List<int> pick_random_points(int n, int lower, int upper) {
    List<int> points;

    // int new_point = rand() % (upper - lower) + lower;

    for (int i = 0; i < n; i++) {
        int evenly_spaced = i * (upper - lower) / n + lower;
        int randomization = rand() % (upper - lower) / n;
        randomization -= randomization / 2;
        int new_point = evenly_spaced + randomization;

        points.push(new_point);
    }

    return points;
}

Powerup* instance_random_powerup(Position position) {
    int random = std::rand() % 5;
    int random_value;

    switch (random) {
        case 0:
            random_value = rand() % 100;
            random_value = std::min(random_value - random_value % 5, 5);  // multiplo di 5, min. 5
            return new Coin(position, random_value);
        case 1:
            return new Gun(position);
        case 2:
            return new Heart(position);
        case 3:
            return new Mushroom(position);
        case 4:
            return new Star(position);
        default:
            throw std::runtime_error("Invalid random value");
    }
}
