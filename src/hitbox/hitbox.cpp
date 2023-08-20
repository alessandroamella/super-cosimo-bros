#include "hitbox.hpp"

bool collides(StaticEntity& a, StaticEntity& b) {
    Position a_pos = a.get_position();
    Position b_pos = b.get_position();

    return a_pos.x == b_pos.x && a_pos.y == b_pos.y;
}