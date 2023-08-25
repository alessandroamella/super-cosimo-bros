#include "gun.hpp"

#include "../shared/settings.hpp"

Gun::Gun(Position position)
    : Powerup(position) {}

EntityType Gun::get_entity_type() {
    return EntityType::Gun;
}

const char* Gun::get_render_char() {
    return render_char;
}
