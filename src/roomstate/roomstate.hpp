#ifndef _ROOMSTATE_HPP_
#define _ROOMSTATE_HPP_

#include "../room/room.hpp"

class RoomState {
   private:
    Room* room;
    int difficulty;

   public:
    RoomState(Room* room, int difficulty);

    Room* get_room();
    int get_difficulty();
};

#endif  // _ROOMSTATE_HPP_
