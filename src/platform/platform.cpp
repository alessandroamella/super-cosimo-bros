#include "platform.hpp"

#include "../shared/functions.hpp"

// position is lower-left, ur is upper-right
Platform::Platform(Position ll, Position ur)
    : StaticEntity(ll), ur(ur) {
}

Position Platform::get_ur() {
    return ur;
}

bool Platform::is_above(Position input_pos) {
    return input_pos.y >= ur.y && is_in(input_pos.x, position.x, ur.x);
}

bool Platform::is_below(Position input_pos) {
    return input_pos.y <= position.y && is_in(input_pos.x, position.x, ur.x);
}

bool Platform::is_on_top(Position input_pos) {
    return input_pos.y - 1 == ur.y && is_in(input_pos.x, position.x, ur.x);
}

bool Platform::is_inside(Position input_pos) {
    return is_in(input_pos.x, position.x, ur.x) && is_in(input_pos.y, position.y, ur.y);
}

bool Platform::is_touching_ceiling(Position input_pos) {
    return input_pos.y + 1 == position.y && is_in(input_pos.x, position.x, ur.x);
}
