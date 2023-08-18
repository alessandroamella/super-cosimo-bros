#include "room.hpp"

Room::Room(int floor[]) : floor{} {
    for (int i = 0; i < GAME_WIDTH; i++) {
        this->floor[i] = floor[i];
    }
}

void Room::load() {
    // TODO implementa: fai partire i nemici bla bla (boh)
}

int Room::get_floor_at(int x) {
    return floor[x];
};

int Room::get_ceiling_at(int x) {
    // TODO in futuro puo' tornare utile se si implementa un tetto
    return GAME_HEIGHT;
}