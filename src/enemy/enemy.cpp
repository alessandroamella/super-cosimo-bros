#include "enemy.hpp"

Enemy::Enemy(Position position, List<int>* floor, List<int>* ceiling, List<Platform>* platforms)
    : RigidEntity(position, floor, ceiling, platforms),
      health(ENEMY_STARTING_HEALTH),
      is_dead(false),
      next_projectile_delay(std::chrono::steady_clock::now() + std::chrono::milliseconds(PROJECTILE_DELAY_MS)) {}

int Enemy::get_health() {
    return health;
}

void Enemy::remove_health() {
    health = std::max(health - 1, 0);
}

void Enemy::start_walking() {
    vel_x = ENEMY_VEL;

    if (should_change_direction()) {
        change_direction();
    }
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

bool Enemy::has_pit() {
    Position after_pos = get_after_pos();
    return after_pos.y != position.y;
}

bool Enemy::should_change_direction() {
    bool collision_left = has_wall_on_left() || has_pit();
    bool collision_right = has_wall_on_right() || has_pit();
    bool collides_platform = collides_with_platform();

    auto status = "collision_left=" + std::to_string(collision_left) +
                  " collision_right=" + std::to_string(collision_right) +
                  " collides_platform=" + std::to_string(collides_platform);

    // int n_true = collision_left + collision_right + collides_platform;

    // if (n_true > 1)
    //     throw std::runtime_error("Enemy::should_change_direction " + std::to_string(n_true) + " time(s): " + status);

    // throw std::runtime_error(status);

    return collision_left || collision_right || collides_platform;
}

void Enemy::change_direction() {
    vel_x = -vel_x;
}

bool Enemy::has_wall_on_left() {
    Position after_pos = get_after_pos();
    return after_pos.x <= 2 || floor->at(after_pos.x - 2) > after_pos.y;
}

bool Enemy::has_wall_on_right() {
    Position after_pos = get_after_pos();
    return after_pos.x >= GAME_WIDTH - 2 || floor->at(after_pos.x + 1) > after_pos.y;
}

bool Enemy::should_shoot() {
    return !is_dead && std::chrono::steady_clock::now() > next_projectile_delay;
}

void Enemy::reset_shoot() {
    int random_delay_sec = (rand() % ENEMY_SHOOTING_MAX_DELAY_SEC) + 1;
    next_projectile_delay = std::chrono::steady_clock::now() + std::chrono::seconds(random_delay_sec);
}

void Enemy::tick() {
    if (is_dead)
        return;

    Position cur_pos = position;

    apply_gravity();
    clamp_velocity();

    if (should_change_direction()) {
        change_direction();
    }

    move_based_on_vel();
    clamp_position();

    last_position = cur_pos;
}
