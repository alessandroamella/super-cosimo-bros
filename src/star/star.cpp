#include "star.hpp"

#include "../shared/settings.hpp"

Star::Star(Position position)
    : Powerup(position) {}

const char* Star::get_render_char() {
    return render_char;
}

EntityType Star::get_entity_type() {
    return EntityType::Star;
}
