#include "mushroom.hpp"

#include "../shared/settings.hpp"

Mushroom::Mushroom(Position position) : Powerup(position) {}

EntityType Mushroom::get_entity_type() {
    return EntityType::Mushroom;
}
