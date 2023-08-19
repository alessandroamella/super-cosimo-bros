#include "staticentity.hpp"

StaticEntity::StaticEntity(Position position) : position(position) {}

Position StaticEntity::get_position() { return position; }
