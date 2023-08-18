#ifndef _LEVEL_HPP_
#define _LEVEL_HPP_

#include "../list/list.hpp"
#include "../room/room.hpp"

class Level {
   public:
    Level(List<Room> rooms, const char* title);
    void load_next_room();
    bool is_last_room();
    Room get_cur_room();

   private:
    List<Room> rooms;
    size_t cur_room_index;
    const char* title;
};

#endif  // _LEVEL_HPP_
