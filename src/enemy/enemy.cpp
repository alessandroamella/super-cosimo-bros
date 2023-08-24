#include "enemy.hpp"

Enemy::Enemy(GameTimer& timer, Position position, List<int> floor, List<int> ceiling)
    : RigidEntity(timer, position, floor, ceiling), health(ENEMY_STARTING_HEALTH), is_dead(false) {}

int Enemy::get_health() {
    return health;
}

void Enemy::remove_health() {
    health = std::max(health - 1, 0);
}

void Enemy::start_walking() {
    vel_x = ENEMY_WALK_VEL;
}

void Enemy::stop_walking() {
    vel_x = 0;
}

bool Enemy::get_is_dead() {
    return is_dead;
}

void Enemy::set_is_dead(bool _is_dead) {
    is_dead = _is_dead;
}

bool Enemy::has_pit_on_left() {
    return position.x < 2 || position.y - 2 >= floor.at(position.x - 1);
}

bool Enemy::has_pit_on_right() {
    return position.x >= GAME_WIDTH - 2 || position.y - 2 >= floor.at(position.x + 1);
}

bool Enemy::should_change_direction() {
    return has_wall_on_left() || has_wall_on_right() || has_pit_on_left() || has_pit_on_right();
}

void Enemy::change_direction() {
    vel_x = -vel_x;
}

bool Enemy::has_wall_on_left() {
    return position.x <= 2 || floor.at(position.x - 2) > position.y;
}

bool Enemy::has_wall_on_right() {
    return position.x >= GAME_WIDTH - 2 || floor.at(position.x + 1) > position.y;
}

void Enemy::tick() {
    if (is_dead)
        return;

    Position cur_pos = position;

    if (should_change_direction()) {
        change_direction();
    }

    // apply_gravity();
    // clamp_velocity();
    move_based_on_vel();
    clamp_position();

    last_position = cur_pos;
}
