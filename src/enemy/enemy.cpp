#include "enemy.hpp"

Enemy::Enemy(GameTimer& timer, Position position, List<int> floor, List<int> ceiling, List<Platform>& platforms)
    : RigidEntity(timer, position, floor, ceiling, platforms),
      health(ENEMY_STARTING_HEALTH),
      is_dead(false) {}

int Enemy::get_health() {
    return health;
}

void Enemy::remove_health() {
    health = std::max(health - 1, 0);
}

void Enemy::start_walking() {
    vel_x = ENEMY_WALK_VEL;

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

bool Enemy::has_pit_on_left() {
    Position after_pos = get_after_pos();
    return after_pos.x <= 2 || floor.at(after_pos.x - 1) > after_pos.y;
}

bool Enemy::has_pit_on_right() {
    Position after_pos = get_after_pos();
    return after_pos.x >= GAME_WIDTH - 2 || floor.at(after_pos.x + 1) > after_pos.y;
}

bool Enemy::should_change_direction() {
    bool collision_left = has_wall_on_left() || has_pit_on_left();
    bool collision_right = has_wall_on_right() || has_pit_on_right();
    bool collides_platform = collides_with_platform();

    auto status = "collision_left=" + std::to_string(collision_left) +
                  " collision_right=" + std::to_string(collision_right) +
                  " collides_platform=" + std::to_string(collides_platform);

    int n_true = collision_left + collision_right + collides_platform;

    if (n_true > 1)
        throw std::runtime_error("Enemy::should_change_direction " + std::to_string(n_true) + " time(s): " + status);

    // throw std::runtime_error(status);

    return collision_left || collision_right || collides_platform;
}

void Enemy::change_direction() {
    vel_x = -vel_x;
}

bool Enemy::collides_with_platform() {
    for (int i = 0; i < platforms.length(); i++) {
        Platform& platform = platforms.at(i);
        Position after_pos = get_after_pos();

        if (platform.is_inside(after_pos))
            return true;
        else if (platform.is_x_within(position.x) && platform.get_top_y(position.x) == position.y - 1 && (!platform.is_x_within(after_pos.x) || platform.get_top_y(after_pos.x) != after_pos.y - 1)) {
            // check for adjacent platform
            bool adjacent_platform = false;

            for (int j = 0; j < platforms.length(); j++) {
                Platform& _platform = platforms.at(j);

                if (_platform.is_x_within(after_pos.x) && _platform.get_top_y(after_pos.x) == position.y - 1)
                    adjacent_platform = true;
            }

            if (!adjacent_platform)
                return true;
        }
    }

    return false;
}

Position Enemy::get_after_pos() {
    return (Position){.x = position.x + vel_x, .y = position.y + vel_y};
}

bool Enemy::has_wall_on_left() {
    Position after_pos = get_after_pos();
    return after_pos.x <= 2 || floor.at(after_pos.x - 1) > after_pos.y;
}

bool Enemy::has_wall_on_right() {
    Position after_pos = get_after_pos();
    return after_pos.x >= GAME_WIDTH - 2 || floor.at(after_pos.x + 1) > after_pos.y;
}

void Enemy::tick() {
    if (is_dead)
        return;

    Position cur_pos = position;

    // apply_gravity();
    // clamp_velocity();
    move_based_on_vel();
    clamp_position();

    if (should_change_direction()) {
        change_direction();
    }

    last_position = cur_pos;
}
