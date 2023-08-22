#ifndef _PLATFORM_HPP_
#define _PLATFORM_HPP_

#include "../list/list.hpp"
#include "../staticentity/staticentity.hpp"

class Platform : public StaticEntity {
   protected:
    Position ur;  // upper right position

   public:
    Platform(Position ll, Position ur);

    Position get_ur();

    bool is_above(Position position);
    bool is_below(Position position);
    bool is_on_top(Position position);
    bool is_inside(Position position);
    bool is_touching_ceiling(Position position);
};

#endif  // _PLATFORM_HPP_
