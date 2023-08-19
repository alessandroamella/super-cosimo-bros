#include "room.hpp"

Room::Room(List<int> floor) {
    for (int i = 0; i < GAME_WIDTH; i++) {
        floor.at(i) = floor.at(i);
    }
}

void Room::load() {
    // TODO implementa: fai partire i nemici bla bla (boh)
}

int Room::get_floor_at(int x) { return floor.at(x); };

int Room::get_ceiling_at(int x) {
    // TODO in futuro puo' tornare utile se si implementa un tetto
    return GAME_HEIGHT;
}