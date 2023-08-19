#ifndef _LEVEL_HPP_
#define _LEVEL_HPP_

#include "../list/list.hpp"
#include "../room/room.hpp"

class LevelManager {
   public:
    LevelManager(List<Room> rooms);
    void load_next_room();
    bool is_last_room();
    Room get_cur_room();

    // prova

   private:
    List<Room> rooms;
    List<Room> visited_rooms;
    size_t cur_room_index;
};

#endif  // _LEVEL_HPP_
