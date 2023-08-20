#include "levelmanager.hpp"

#include <stdlib.h>

LevelManager::LevelManager(List<Room> *rooms)
    : cur_room_index(0), visited_rooms(), rooms(rooms) {
    visited_rooms.push(cur_room_index);
}

Room *LevelManager::get_cur_room() {
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

void LevelManager::tick() {
    get_cur_room()->tick();
}
