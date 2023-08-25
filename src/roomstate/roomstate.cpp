#include "roomstate.hpp"

RoomState::RoomState(Room* room, int difficulty)
    : room(room),
      difficulty(difficulty) {}

Room* RoomState::get_room() {
    return room;
}

int RoomState::get_difficulty() {
    return difficulty;
}
