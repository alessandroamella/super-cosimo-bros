#ifndef _MAPS_HPP_
#define _MAPS_HPP_

#include "../list/list.hpp"
#include "../room/room.hpp"
#include "../shared/position.hpp"
#include "../shared/settings.hpp"

class Maps {
   protected:
    List<Room*> rooms;

   public:
    Maps();
    Room* get_room(int index);
    void cleanup();
    // eccetera per tutte le altre stanze
};

#endif  // _MAPS_HPP_