#include "star.hpp"

#include "../shared/settings.hpp"

Star::Star(Position position) : Powerup(position) {}

EntityType Star::get_entity_type() {
    return EntityType::Star;
}
