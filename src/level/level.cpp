#include "level.hpp"

Level::Level(List<Room> rooms, const char* title) : rooms(rooms), title(title), cur_room_index(0) {}

void Level::load_next_room() {
    if (cur_room_index < rooms.length() - 1) {
        cur_room_index++;
        rooms.at(cur_room_index).load();
    }
}

bool Level::is_last_room() {
    return cur_room_index == rooms.length() - 1;
}

Room Level::get_cur_room() {
    return rooms.at(cur_room_index);
}