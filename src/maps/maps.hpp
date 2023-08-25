#ifndef _MAPS_HPP_
#define _MAPS_HPP_

#include "../list/list.hpp"
#include "../room/room.hpp"
#include "../shared/position.hpp"
#include "../shared/settings.hpp"

class Maps {
   protected:
   public:
    static Room layout1();
    static Room layout2();
    static Room layout3();

    // eccetera per tutte le altre stanze
};

#endif  // _MAPS_HPP_