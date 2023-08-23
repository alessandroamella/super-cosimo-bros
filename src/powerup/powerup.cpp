#include "powerup.hpp"

Powerup::Powerup(Position position) : StaticBox((Position){.x = position.x - 2, .y = position.y + 1}, (Position){.x = position.x + 2, .y = position.y - 1}), is_active(true) {}

bool Powerup::get_is_active() {
    return is_active;
}

void Powerup::set_is_active(bool _is_active) {
    is_active = _is_active;
}

const char* Powerup::get_render_char() {
    return render_char;
}
