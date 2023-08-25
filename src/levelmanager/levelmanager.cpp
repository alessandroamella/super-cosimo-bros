#include "levelmanager.hpp"

#include <stdlib.h>

#include "../shared/functions.hpp"
#include "../shared/settings.hpp"

LevelManager::LevelManager(List<Room>* rooms, GameTimer game_timer)
    : cur_visited_room_index(0),
      visited_rooms(),  // chiama in automatico il costruttore di List di default
      rooms(rooms),
      game_timer(game_timer),
      difficulty(STARTING_DIFFICULTY),
      difficulty_target(STARTING_DIFFICULTY),
      should_load_new_room(false),
      should_load_prev_room(false) {
    RoomState starting_room_state(get_random_room(), difficulty_target);
    visited_rooms.push(starting_room_state);
}

Room* LevelManager::get_cur_room() {
    return visited_rooms.at(cur_visited_room_index).get_room();
}

bool LevelManager::no_more_rooms_to_load() {
    return visited_rooms.length() == rooms->length();
}

Room* LevelManager::get_random_room() {
    int index = rand() % rooms->length();

    // prima carica le stanze non visitate
    if (no_more_rooms_to_load())
        return &rooms->at(index);

    // poi anche quelle gia' visitate
    while (is_room_visited(&rooms->at(index))) {
        index = rand() % rooms->length();
    }

    return &rooms->at(index);
}

void LevelManager::update_difficulty_to_print() {
    if (difficulty < difficulty_target)
        difficulty++;
    else if (difficulty > difficulty_target)
        difficulty--;
}

bool LevelManager::is_room_visited(Room* room) {
    for (int i = 0; i < visited_rooms.length(); i++) {
        if (visited_rooms.at(i).get_room() == room)
            return true;
    }

    return false;
}

void LevelManager::place_enemies_randomly(int enemy_count, int start_padding) {
    List<int> x_positions = pick_random_points(enemy_count, 1 + start_padding, get_cur_room()->get_width() - 1, 5);

    for (int i = 0; i < enemy_count; i++) {
        int x = x_positions.at(i);
        int platform_y = get_cur_room()->get_platform_at(x);
        int y = platform_y != -1 ? platform_y + 1 : get_cur_room()->get_floor_at(x) + 1;

        // throw std::runtime_error("x=" + std::to_string(x) + " platform_y=" + std::to_string(platform_y) + " y=" + std::to_string(y));

        Enemy enemy(game_timer, (Position){x, y}, get_cur_room()->get_floor(), get_cur_room()->get_ceiling(), get_cur_room()->get_platforms());

        get_cur_room()->add_enemy(enemy);
    }
}

int LevelManager::get_difficulty() {
    return visited_rooms.at(cur_visited_room_index).get_difficulty();
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
        difficulty_target += visited_rooms.length() / 2;

        RoomState room_to_load = RoomState(get_random_room(), difficulty_target);
        visited_rooms.push(room_to_load);

        cur_visited_room_index++;
        place_enemies_randomly(get_difficulty(), ENEMY_DISTANCE_FROM_START);
    } else {
        cur_visited_room_index--;
    }

    get_cur_room()->load();
}

void LevelManager::load_first_room() {
    cur_visited_room_index = 0;
    difficulty = STARTING_DIFFICULTY;
    difficulty_target = STARTING_DIFFICULTY;

    place_enemies_randomly(get_difficulty(), ENEMY_DISTANCE_FROM_START);
    get_cur_room()->load();
}

void LevelManager::restart_from_first_room() {
    cur_visited_room_index = 0;
    difficulty = STARTING_DIFFICULTY;
    difficulty_target = STARTING_DIFFICULTY;

    get_cur_room()->load();
}

void LevelManager::tick(Position player_position) {
    update_difficulty_to_print();
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
    if (is_in_start_region(position))
        // TODO decommenta
        // if (get_visited_rooms_count() > 1)
        should_load_prev_room = true;
    else if (is_in_end_region(position))
        should_load_new_room = true;
}
