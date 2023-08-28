#include "maps.hpp"

#include "../powerup/powerup.hpp"
#include "../staticbox/staticbox.hpp"

#include "layouts/layout1.hpp"
#include "layouts/layout2.hpp"
#include "layouts/layout3.hpp"

#include "layouts/layout4.hpp"
#include "layouts/layout5.hpp"
#include "layouts/layout6.hpp"
#include "layouts/layout7.hpp"
#include "layouts/layout8.hpp"
#include "layouts/layout9.hpp"
#include "layouts/layout10.hpp"
#include "layouts/layout11.hpp"
#include "layouts/layout12.hpp"


Maps::Maps() {
    rooms = List<Room*>();

    rooms.push(layout1());
    rooms.push(layout2());
    rooms.push(layout3());

    rooms.push(layout4());
    rooms.push(layout5());
    rooms.push(layout6());
    rooms.push(layout7());
    rooms.push(layout8());
    rooms.push(layout9());
    rooms.push(layout10());
    rooms.push(layout11());
    rooms.push(layout12());
}

List<Room*>* Maps::get_all_rooms() {
    return &rooms;
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
