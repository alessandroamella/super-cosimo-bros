#ifndef _STATICENTITY_HPP_
#define _STATICENTITY_HPP_

#include <ncurses.h>

#include "../shared/position.hpp"
#include "../shared/settings.hpp"

class StaticEntity {
   protected:
    Position position;
    EntityType type;

   public:
    StaticEntity(Position position);
    Position get_position();
    EntityType get_entity_type();
};

#endif  // _STATICENTITY_HPP_
