#include "coin.hpp"

#include <iostream>

#include "../shared/settings.hpp"

Coin::Coin(Position position, int value) : Powerup(position), value(value) {}

EntityType Coin::get_entity_type() {
    return EntityType::Coin;
}

const char* Coin::get_render_char() {
    return std::to_string(value).c_str();
}

int Coin::get_value() {
    return value;
}
