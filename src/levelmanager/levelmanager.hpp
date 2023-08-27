#ifndef _LEVELMANAGER_HPP_
#define _LEVELMANAGER_HPP_

#include "../list/list.hpp"
#include "../room/room.hpp"

#include "../roomstate/roomstate.hpp"

class LevelManager {
   private:
    GameTimer* game_timer;
    List<Room*>* rooms;

    List<RoomState> visited_rooms;
    int cur_visited_room_index;

    bool should_load_new_room;
    bool should_load_prev_room;

    bool is_first_room();
    Room* get_random_room();

    bool is_in_start_region(Position position);
    bool is_in_end_region(Position position);
    void handle_enter_region(Position position);

    void place_enemies_randomly(int enemy_count, int start_padding);
    void place_powerups_randomly(int powerup_count, int start_padding);
    int get_powerup_number(int difficulty);

   public:
    LevelManager(List<Room*>* rooms, GameTimer* game_timer);

    Room* get_cur_room();
    int get_cur_difficulty();
    int get_visited_rooms_count();

    bool should_change_room();
    void execute_room_change();

    void load_first_room();
    void restart_from_first_room();

    int get_cur_visited_room_index() const;
    int get_total_visited_room_count();

    void cleanup();

    void tick(Position player_position);
};

#endif  // _LEVELMANAGER_HPP_
