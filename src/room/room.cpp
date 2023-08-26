#include "room.hpp"

#include "../shared/functions.hpp"

Room::Room(const int room_id, List<int> floor, List<int> ceiling, List<Platform> platforms, int width, int height, StaticBox start_region, StaticBox end_region)
    : room_id(room_id),
      powerups(),
      floor(floor),
      ceiling(ceiling),
      width(width),
      height(height),
      platforms(platforms),
      enemies(List<Enemy>()),
      start_region(start_region),
      end_region(end_region) {
    if (floor.length() != width)
        throw std::invalid_argument("floor room length must be equal to width");
}

// non copiare nemici!!
Room::Room(const Room& base)
    : room_id(base.room_id), powerups(base.powerups), floor(base.floor), ceiling(base.ceiling), width(base.width), height(base.height), platforms(base.platforms), enemies(), start_region(base.start_region), end_region(base.end_region) {
}

Room* Room::clone() const {
    return new Room(*this);
}

int Room::get_room_id() {
    return room_id;
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
    for (int i = 0; i < projectiles.length(); i++) {
        remove_projectile(projectiles.at(i));
    }
}

void Room::cleanup() {
    for (int i = 0; i < powerups.length(); i++) {
        delete powerups.at(i);
    }
    for (int i = 0; i < projectiles.length(); i++) {
        delete projectiles.at(i);
    }
}

void Room::tick() {
    for (int i = 0; i < enemies.length(); i++) {
        enemies.at(i).tick();
    }
    for (int i = 0; i < projectiles.length(); i++) {
        projectiles.at(i)->tick();
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

// ATTENTO AL `nullptr` (CONTROLLA)
Platform* Room::get_platform_at(int x) {
    if (x < 0 || x >= width)
        throw std::invalid_argument(
            "get_platform_at: x=" + std::to_string(x) +
            " must be in range [0, width=" + std::to_string(width) + ")");

    for (int i = 0; i < platforms.length(); i++) {
        if (platforms.at(i).is_x_within(x))
            return &platforms.at(i);
    }

    return nullptr;
}

List<int>& Room::get_floor() {
    return floor;
}

List<int>& Room::get_ceiling() {
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

List<Powerup*>& Room::get_powerups() {
    return powerups;
}

List<Enemy>& Room::get_enemies() {
    return enemies;
}

List<Projectile*>& Room::get_projectiles() {
    return projectiles;
}

StaticBox& Room::get_start_region() {
    return start_region;
}

StaticBox& Room::get_end_region() {
    return end_region;
}

Position Room::get_player_start_position() {
    return (Position){.x = start_region.get_ur().x + PLAYER_START_POS_OFFSET, .y = start_region.get_position().y + 2};
}

void Room::add_enemy(Enemy enemy) {
    enemies.push(enemy);
}

void Room::add_powerup(Powerup* powerup) {
    powerups.push(powerup);
}

void Room::add_projectile(Projectile* projectile) {
    projectiles.push(projectile);
}

void Room::remove_projectile(Projectile* projectile) {
    // confronto tra puntatori, tanto se controllo usando .at ottengo lo stesso puntatore dunque funziona
    for (int i = 0; i < projectiles.length(); i++) {
        if (projectiles.at(i) == projectile) {
            delete projectiles.pop(i);
            return;
        }
    }
}
