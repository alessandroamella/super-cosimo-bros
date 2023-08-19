#include "room.hpp"

Room::Room(List<int> floor, int width, int height)
    : floor(floor), width(width), height(height) {
    if (floor.length() != width)
        throw std::invalid_argument("floor room length must be equal to width");
}

void Room::load() {
    // TODO implementa: fai partire i nemici bla bla (boh)
}

int Room::get_floor_at(int x) {
    if (x < 0 || x >= width)
        throw std::invalid_argument(
            "get_floor_at: x=" + std::to_string(x) +
            " must be in range [0, width=" + std::to_string(width) + ")");

    return floor.at(x);
};

int Room::get_ceiling_at(int x) {
    if (x < 0 || x >= width)
        throw std::invalid_argument(
            "get_ceiling_at: x=" + std::to_string(x) +
            " must be in range [0, width=" + std::to_string(width) + ")");

    // TODO in futuro puo' tornare utile se si implementa un tetto
    return height;
}

int Room::get_width() {
    return width;
}

int Room::get_height() {
    return height;
}

bool Room::is_within_bounds(Position position) {
    return position.x >= 0 && position.x < width && position.y >= 0 &&
           position.y < height;
}
