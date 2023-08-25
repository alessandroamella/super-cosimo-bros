#include "levelmanager.hpp"

#include <math.h>
#include <stdlib.h>

#include "../shared/functions.hpp"
#include "../shared/settings.hpp"

LevelManager::LevelManager(List<Room*>* rooms, GameTimer* game_timer)
    : cur_visited_room_index(0),
      visited_rooms(),  // chiama in automatico il costruttore di List di default
      rooms(rooms),
      game_timer(game_timer),
      should_load_new_room(false),
      should_load_prev_room(false) {
    RoomState starting_room_state(get_random_room(), STARTING_DIFFICULTY);
    visited_rooms.push(starting_room_state);
}

Room* LevelManager::get_cur_room() {
    return visited_rooms.at(cur_visited_room_index).get_room();
}

int LevelManager::get_cur_difficulty() {
    return visited_rooms.at(cur_visited_room_index).get_difficulty();
}

Room* LevelManager::get_random_room() {
    int index = rand() % rooms->length();

    if (visited_rooms.length() > 0) {
        while (rooms->at(index)->get_room_id() == get_cur_room()->get_room_id()) {
            index = rand() % rooms->length();
        }
    }

    Room* base_room = rooms->at(index);
    return base_room->clone();
}

bool LevelManager::is_first_room() {
    return cur_visited_room_index == 0;
}

void LevelManager::place_enemies_randomly(int enemy_count, int start_padding) {
    List<int> x_positions = pick_random_points(enemy_count, 1 + start_padding, get_cur_room()->get_width() - 1);

    for (int i = 0; i < enemy_count; i++) {
        int x = x_positions.at(i);
        Platform* platform_at_x = get_cur_room()->get_platform_at(x);
        int platform_y = platform_at_x != nullptr ? platform_at_x->get_top_y(x) : -1;
        int y = platform_y != -1 ? platform_y + 1 : get_cur_room()->get_floor_at(x) + 1;

        // throw std::runtime_error("x=" + std::to_string(x) + " platform_y=" + std::to_string(platform_y) + " y=" + std::to_string(y));

        Enemy enemy(game_timer, (Position){x, y}, &get_cur_room()->get_floor(), &get_cur_room()->get_ceiling(), &get_cur_room()->get_platforms());

        get_cur_room()->add_enemy(enemy);
    }
}

void LevelManager::place_powerups_randomly(int powerup_count, int start_padding) {
    List<int> x_positions = pick_random_points(powerup_count, 1 + start_padding, get_cur_room()->get_width() - 1);

    for (int i = 0; i < powerup_count; i++) {
        int x = x_positions.at(i);
        Platform* platform_at_x = get_cur_room()->get_platform_at(x);
        int platform_y = platform_at_x != nullptr ? platform_at_x->get_top_y(x) : -1;
        int y = platform_y != -1 ? platform_y + 1 : get_cur_room()->get_floor_at(x) + 1;

        y += 5;
        bool place_found = true;
        // controlla che non sia dentro alcuna altra piattaforma
        do {
            y++;
            place_found = true;
            Position pos = (Position){x, y};
            for (int j = 0; j < get_cur_room()->get_platforms().length(); j++) {
                Platform _platform = get_cur_room()->get_platforms().at(j);
                if (_platform.is_inside(pos) || _platform.is_on_top(pos) || _platform.is_touching_ceiling(pos) || y > _platform.get_ur().y + 5) {
                    place_found = false;
                } else if (is_in(x, 3, GAME_WIDTH - 3)) {
                    for (int k = 0; i < k; k++) {
                        if (get_cur_room()->get_floor_at(x + k - 2) >= y - 2)
                            place_found = false;
                        for (int l = 0; l < 4; j++) {
                            if (_platform.is_inside((Position){.x = x + k - 2, .y = y + l - 2}))
                                place_found = false;
                            else if (get_cur_room()->get_end_region().is_inside((Position){.x = x + k - 2, .y = y + l - 2}))
                                place_found = false;
                            else if (get_cur_room()->get_start_region().is_inside((Position){.x = x + k - 2, .y = y + l - 2}))
                                place_found = false;
                        }
                    }
                }
            }
        } while (!place_found && y <= get_cur_room()->get_height() - 5);
        if (!place_found) {
            continue;
        }

        Position powerup_pos = (Position){x, y};

        Powerup* powerup = instance_random_powerup(powerup_pos);
        get_cur_room()->add_powerup(powerup);
    }
}

int LevelManager::get_powerup_number(int x) {
    return (int)(-std::pow(x, 0.75) + 8.0);
}

int LevelManager::get_visited_rooms_count() {
    return visited_rooms.length();
}

bool LevelManager::should_change_room() {
    return should_load_prev_room || should_load_new_room;
}

void LevelManager::execute_room_change() {
    if (!should_change_room())
        throw std::runtime_error("LevelManager::execute_room_change: !should_change_room()");

    get_cur_room()->freeze();

    if (should_load_new_room) {
        bool was_already_visited = cur_visited_room_index + 1 < visited_rooms.length();

        int new_difficulty = get_cur_difficulty() + 1;

        cur_visited_room_index++;

        if (!was_already_visited) {
            cur_visited_room_index--;
            RoomState room_to_load = RoomState(get_random_room(), new_difficulty);
            visited_rooms.push(room_to_load);
            cur_visited_room_index++;

            place_enemies_randomly(new_difficulty, ENEMY_DISTANCE_FROM_START);
            place_powerups_randomly(get_powerup_number(new_difficulty), POWERUP_DISTANCE_FROM_START);
        }

        if (cur_visited_room_index >= visited_rooms.length())
            throw std::runtime_error("LevelManager::execute_room_change: cur_visited_room_index >= visited_rooms.length()");

    } else if (should_load_prev_room) {
        cur_visited_room_index--;

        if (cur_visited_room_index < 0)
            throw std::runtime_error("LevelManager::execute_room_change: cur_visited_room_index < 0");
    } else {
        throw std::runtime_error("LevelManager::execute_room_change: should_change_room() but no condition was met");
    }

    should_load_new_room = false;
    should_load_prev_room = false;

    get_cur_room()->load();
}

void LevelManager::load_first_room() {
    // RoomState della prima stanza viene gia' aggiunto nel costruttore

    cur_visited_room_index = 0;

    place_enemies_randomly(get_cur_difficulty(), ENEMY_DISTANCE_FROM_START);
    place_powerups_randomly(1, POWERUP_DISTANCE_FROM_START);
    get_cur_room()->load();
}

void LevelManager::restart_from_first_room() {
    get_cur_room()->freeze();
    cur_visited_room_index = 0;
    get_cur_room()->load();
}

void LevelManager::cleanup() {
    for (int i = 0; i < visited_rooms.length(); i++) {
        Room* room = visited_rooms.at(i).get_room();
        room->cleanup();
        delete room;
    }
}

void LevelManager::tick(Position player_position) {
    handle_enter_region(player_position);

    get_cur_room()->tick();
}

bool LevelManager::is_in_start_region(Position position) {
    return get_cur_room()->get_start_region().is_inside(position);
}

bool LevelManager::is_in_end_region(Position position) {
    return get_cur_room()->get_end_region().is_inside(position);
}

void LevelManager::handle_enter_region(Position position) {
    if (is_in_start_region(position) && !is_first_room())
        should_load_prev_room = true;
    else if (is_in_end_region(position))
        should_load_new_room = true;
}
