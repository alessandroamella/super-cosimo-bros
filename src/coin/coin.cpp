#include "coin.hpp"

#include <iostream>

#include "../shared/settings.hpp"

Coin::Coin(Position position, int value)
    : Powerup(position), value(value) {}

EntityType Coin::get_entity_type() {
    return EntityType::Coin;
}

const char* Coin::get_render_char() {
    return std::to_string(value).c_str();
}

int Coin::get_value() {
    return value;
}

int Coin::get_digits() {
    return std::to_string(value).length();
}

int Coin::generate_random_coin_value() {
    int random_value = rand() % 25;
    return std::max(random_value - random_value % 5, 5);  // multiplo di 5, min. 5
}
