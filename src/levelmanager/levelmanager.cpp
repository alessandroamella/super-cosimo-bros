#include "levelmanager.hpp"

#include <stdlib.h>

#include "../shared/functions.hpp"
#include "../shared/settings.hpp"

LevelManager::LevelManager(List<Room>* rooms, GameTimer game_timer)
    : cur_room_index(0),
      visited_rooms(),
      rooms(rooms),
      game_timer(game_timer),
      difficulty(STARTING_DIFFICULTY),
      difficulty_target(STARTING_DIFFICULTY) {
    visited_rooms.push(cur_room_index);
}

Room* LevelManager::get_cur_room() {
    return &rooms->at(cur_room_index);
}

void LevelManager::load_random_room() {
    size_t random_room_index = rand() % rooms->length();

    while (visited_rooms.contains(random_room_index))
        random_room_index = rand() % rooms->length();

    cur_room_index = random_room_index;
    get_cur_room()->load();
}

bool LevelManager::is_room_visited(size_t index) {
    return visited_rooms.contains(index);
}

void LevelManager::place_enemies_randomly(int enemy_count, int start_padding) {
    List<int> x_positions = pick_random_points(enemy_count, 1 + start_padding, get_cur_room()->get_width() - 1);

    for (int i = 0; i < enemy_count; i++) {
        get_cur_room()->add_enemy(Enemy(game_timer, (Position){.x = x_positions.at(i), .y = get_cur_room()->get_floor_at(x_positions.at(i)) + 1}, get_cur_room()->get_floor(), get_cur_room()->get_ceiling()));
    }
}

int LevelManager::get_difficulty() {
    if (difficulty < difficulty_target)
        difficulty++;
    return difficulty;
}

void LevelManager::increase_difficulty() {
    difficulty_target = difficulty + (int)(2 * visited_rooms.length() / 3);
}

void LevelManager::tick() {
    get_cur_room()->tick();
}
