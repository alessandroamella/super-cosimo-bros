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

bool StaticBox::is_x_within(int x) {
    // TODO + 1 e' giusto?
    return is_in(x, position.x + 1, ur.x);
}

int StaticBox::get_top_y(int x) {
    // Prima puoi usare is_x_within per controllare che x sia nel range
    if (x < position.x || x > ur.x)
        throw std::invalid_argument(
            "get_top_y: x=" + std::to_string(x) +
            " must be in range [" + std::to_string(position.x) + ", " + std::to_string(ur.x) + "]");

    return ur.y;
}
