#ifndef _ROOM_HPP_
#define _ROOM_HPP_

#include "../shared/position.hpp"
#include "../shared/settings.hpp"

class Room {
   public:
    Room(int floor[]);
    void load();
    int get_floor_at(int x);
    int get_ceiling_at(int x);

   private:
    int floor[GAME_WIDTH];
};

#endif  // _ROOM_HPP_
