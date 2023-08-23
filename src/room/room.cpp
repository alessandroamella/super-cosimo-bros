#include "room.hpp"

#include "../shared/functions.hpp"

Room::Room(GameTimer& timer, List<int> floor, List<int> ceiling, List<Platform> platforms, int width, int height)
    : game_timer(timer), floor(floor), ceiling(ceiling), width(width), height(height), platforms(platforms), enemies(List<Enemy>()), powerups(List<Powerup>()) {
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

int Room::get_height() {
    return height;
}

List<Powerup>& Room::get_powerups() {
    return powerups;
}

List<Enemy>& Room::get_enemies() {
    return enemies;
}

bool Room::is_within_bounds(Position position) {
    return position.x > 0 && position.x < floor.at(position.x) && position.y > 0 && position.y < ceiling.at(position.x);
}

void Room::place_enemies_randomly(int enemy_count, int start_padding) {
    List<int> x_positions = pick_random_points(enemy_count, 1 + start_padding, width - 1);

    for (int i = 0; i < enemy_count; i++) {
        enemies.push(Enemy(game_timer, (Position){.x = x_positions.at(i), .y = get_floor_at(x_positions.at(i)) + 1}, floor, ceiling));
    }
}
