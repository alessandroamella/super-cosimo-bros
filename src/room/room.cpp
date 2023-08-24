#include "room.hpp"

#include "../shared/functions.hpp"

Room::Room(List<Powerup*> powerups, List<int> floor, List<int> ceiling, List<Platform> platforms, int width, int height)
    : powerups(powerups), floor(floor), ceiling(ceiling), width(width), height(height), platforms(platforms), enemies(List<Enemy>()) {
    if (floor.length() != width)
        throw std::invalid_argument("floor room length must be equal to width");
}

void Room::load() {
    for (int i = 0; i < enemies.length(); i++) {
        enemies.at(i).start_walking();
    }
}

void Room::freeze() {
    for (int i = 0; i < enemies.length(); i++) {
        enemies.at(i).stop_walking();
    }
}

void Room::tick() {
    for (int i = 0; i < enemies.length(); i++) {
        enemies.at(i).tick();
    }
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

    return ceiling.at(x);
}

List<int>& Room::get_floor(){
    return floor;
}

 List<int>& Room::get_ceiling(){
    return ceiling;
 }

List<Platform>& Room::get_platforms() {
    return platforms;
}

int Room::get_width() {
    return width;
}

List<int>& Room::get_floor() {
    return floor;
}

List<int>& Room::get_ceiling() {
    return ceiling;
}

int Room::get_height() {
    return height;
}

List<Powerup*>& Room::get_powerups() {
    return powerups;
}

List<Enemy>& Room::get_enemies() {
    return enemies;
}

void Room::add_enemy(Enemy enemy) {
    enemies.push(enemy);
}

bool Room::is_within_bounds(Position position) {
    return position.x > 0 && position.x < floor.at(position.x) && position.y > 0 && position.y < ceiling.at(position.x);
}
