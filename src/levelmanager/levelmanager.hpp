#ifndef _LEVELMANAGER_HPP_
#define _LEVELMANAGER_HPP_

#include "../list/list.hpp"
#include "../room/room.hpp"

#include "../roomstate/roomstate.hpp"

class LevelManager {
   public:
    LevelManager(List<Room>* rooms, GameTimer game_timer);

    Room* get_cur_room();
    int get_difficulty();

    int get_visited_rooms_count();
    void place_enemies_randomly(int enemy_count, int start_padding);

    bool should_change_room();
    void execute_room_change();

    void load_first_room();
    void restart_from_first_room();

    void tick(Position player_position);

   private:
    GameTimer game_timer;
    List<Room>* rooms;

    List<RoomState> visited_rooms;
    int cur_visited_room_index;

    int difficulty;
    int difficulty_target;  // per animazione incremento difficolta'

    bool should_load_new_room;
    bool should_load_prev_room;

    bool is_in_start_region(Position position);
    bool is_in_end_region(Position position);
    void handle_enter_region(Position position);

    bool is_room_visited(Room* room);
    bool no_more_rooms_to_load();

    Room* get_random_room();
    void update_difficulty_to_print();
};

#endif  // _LEVELMANAGER_HPP_
