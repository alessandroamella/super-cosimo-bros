#include "levelmanager.hpp"

LevelManager::LevelManager(List<Room> rooms)
    : rooms(rooms), cur_room_index(0) {}

void LevelManager::load_next_room() {
    if (cur_room_index < rooms.length() - 1) {
        cur_room_index++;
        rooms.at(cur_room_index).load();
    }
}

bool LevelManager::is_last_room() {
    return cur_room_index == rooms.length() - 1;
}

Room LevelManager::get_cur_room() { return rooms.at(cur_room_index); }