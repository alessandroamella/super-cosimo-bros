#ifndef _PLATFORM_HPP_
#define _PLATFORM_HPP_

#include "../list/list.hpp"
#include "../staticbox/staticbox.hpp"

class Platform : public StaticBox {
   public:
    Platform(Position ll, Position ur);
};

#endif  // _PLATFORM_HPP_
