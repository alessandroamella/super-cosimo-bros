#include "staticbox.hpp"

#include "../shared/functions.hpp"

// position is lower-left, ur is upper-right
StaticBox::StaticBox(Position ll, Position ur)
    : StaticEntity(ll), ur(ur) {}

Position StaticBox::get_ur() {
    return ur;
}

bool StaticBox::is_above(Position input_pos) {
    return input_pos.y >= ur.y && is_in(input_pos.x, position.x, ur.x);
}

bool StaticBox::is_below(Position input_pos) {
    return input_pos.y <= position.y && is_in(input_pos.x, position.x, ur.x);
}

bool StaticBox::is_on_top(Position input_pos) {
    return input_pos.y - 1 == ur.y && is_in(input_pos.x, position.x, ur.x);
}

bool StaticBox::is_inside(Position input_pos) {
    return is_in(input_pos.x, position.x, ur.x) && is_in(input_pos.y, position.y, ur.y);
}

bool StaticBox::is_touching_ceiling(Position input_pos) {
    return input_pos.y + 1 == position.y && is_in(input_pos.x, position.x, ur.x);
}
