#include "heart.hpp"

#include "../shared/settings.hpp"

Heart::Heart(Position position) : Powerup(position) {}

EntityType Heart::get_entity_type() {
    return EntityType::Heart;
}

const char* Heart::get_render_char() {
    return render_char;
}
