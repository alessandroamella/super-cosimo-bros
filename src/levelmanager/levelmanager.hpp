#ifndef _LEVELMANAGER_HPP_
#define _LEVELMANAGER_HPP_

#include "../list/list.hpp"
#include "../room/room.hpp"

class LevelManager {
   public:
    LevelManager(List<Room>* rooms, GameTimer game_timer);
    Room* get_cur_room();
    void load_random_room();
    bool is_room_visited(size_t index);
    void place_enemies_randomly(int enemy_count, int start_padding);
    int get_difficulty();
    void increase_difficulty();
    void tick();

   private:
    GameTimer game_timer;
    List<Room>* rooms;
    List<size_t> visited_rooms;
    size_t cur_room_index;
    int difficulty;
    int difficulty_target;  // per animazione incremento difficolta'
};

#endif  // _LEVELMANAGER_HPP_
