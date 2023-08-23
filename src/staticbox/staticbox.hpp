#ifndef _STATICBOX_HPP_
#define _STATICBOX_HPP_

#include "../list/list.hpp"
#include "../staticentity/staticentity.hpp"

class StaticBox : public StaticEntity {
   protected:
    Position ur;  // upper right position

   public:
    StaticBox(Position ll, Position ur);

    Position get_ur();

    bool is_above(Position position);
    bool is_below(Position position);
    bool is_on_top(Position position);
    bool is_inside(Position position);
    bool is_touching_ceiling(Position position);
};

#endif  // _STATICBOX_HPP_
