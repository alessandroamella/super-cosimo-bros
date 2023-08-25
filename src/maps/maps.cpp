#include "maps.hpp"

#include "../powerup/powerup.hpp"
#include "../staticbox/staticbox.hpp"

#include "layouts/layout1.hpp"
#include "layouts/layout2.hpp"
#include "layouts/layout3.hpp"

Maps::Maps() {
    rooms = List<Room*>();

    rooms.push(layout1());
    rooms.push(layout2());
    rooms.push(layout3());
}

Room* Maps::get_room(int index) {
    if (index < 0 || index >= rooms.length()) {
        throw std::invalid_argument(
            "get_room: index=" + std::to_string(index) +
            " must be in range [0, rooms.length()=" + std::to_string(rooms.length()) + ")");
    }

    return rooms.at(index);
}

void Maps::cleanup() {
    for (int i = 0; i < rooms.length(); i++) {
        delete rooms.at(i);
    }
}
