#ifndef _LEVELMANAGER_HPP_
#define _LEVELMANAGER_HPP_

#include "../list/list.hpp"
#include "../room/room.hpp"

class LevelManager {
   public:
    LevelManager(List<Room> *rooms);
    Room *get_cur_room();
    void load_random_room();
    bool is_room_visited(size_t index);
    void tick();

   private:
    List<Room> *rooms;
    List<size_t> visited_rooms;
    size_t cur_room_index;
};

#endif  // _LEVELMANAGER_HPP_
