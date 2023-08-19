#ifndef _STATICENTITY_HPP_
#define _STATICENTITY_HPP_

#include <ncurses.h>

#include "../shared/position.hpp"

class StaticEntity {
   protected:
    Position position;

   public:
    StaticEntity(Position position);
    Position get_position();
};

#endif  // _STATICENTITY_HPP_
