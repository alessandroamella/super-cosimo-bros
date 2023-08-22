#include "player.hpp"

#include <iostream>

#include "../shared/functions.hpp"

Player::Player(GameTimer& timer,
               InputManager& input_manager,
               Position position,
               List<int> floor,
               List<int> ceiling,
               List<Platform>& platforms)
    : RigidEntity(timer, position, floor, ceiling),
      input_manager(input_manager),
      is_jumping(false),
      is_shooting(false),
      health(PLAYER_STARTING_HEALTH),
      platforms(platforms) {}

void Player::run_left() {
    vel_x = -PLAYER_RUN_VEL;
}

void Player::run_right() {
    vel_x = PLAYER_RUN_VEL;
}

void Player::jump() {
    if (!is_jumping) {
        is_jumping = true;
        jump_phase = PlayerJumpPhase::Up1;
    };
}

void Player::update_jump_position() {
    // TODO controlla se sul pavimento

    switch (jump_phase) {
        case PlayerJumpPhase::Stall:
            vel_y = 0;
            break;
        default:
            vel_y += PLAYER_JUMP_VEL;
            break;
    };

    int _jump_phase = ((int)jump_phase + 1);

    if (_jump_phase < jumpPhasesNum)
        jump_phase = (PlayerJumpPhase)_jump_phase;
    else
        is_jumping = false;
}

void Player::process_input() {
    if (input_manager.is_key_pressed((int)PlayerControls::Jump) && (is_on_floor() || is_on_platform()))
        jump();

    if (input_manager.is_key_pressed((int)PlayerControls::RunLeft))
        run_left();
    else if (input_manager.is_key_pressed((int)PlayerControls::WalkLeft))
        move_left();
    else if (input_manager.is_key_pressed((int)PlayerControls::RunRight))
        run_right();
    else if (input_manager.is_key_pressed((int)PlayerControls::WalkRight))
        move_right();
    else if (!is_jumping)
        apply_friction();

    if (input_manager.is_key_pressed((int)PlayerControls::Shoot))
        shoot();
}

void Player::shoot() {
    is_shooting = true;

    // TODO
}

bool Player::is_on_platform() {
    for (int i = 0; i < platforms.length(); i++) {
        Platform& platform = platforms.at(i);

        if (platform.is_on_top(position))
            return true;
    }

    return false;
}

// override: controlla se sta saltando
void Player::apply_gravity() {
    if (is_jumping)
        update_jump_position();
    else if (is_on_floor() || is_on_platform())
        vel_y = std::max(0, vel_y);
    else
        vel_y--;

    // se tocca il soffitto, la vel_y deve essere <= 0
    if (is_touching_ceiling())
        vel_y = clamp(vel_y, vel_y, 0);
};

int Player::get_health() {
    return health;
}

void Player::add_health(int amount) {
    health = std::max(health + amount, PLAYER_MAX_HEALTH);
}

void Player::set_health(int amount) {
    health = clamp(amount, 0, PLAYER_MAX_HEALTH);
}

void Player::remove_health(int amount) {
    health = std::max(health - amount, 0);
}

void Player::clamp_speed_based_on_platforms() {
    for (int i = 0; i < platforms.length(); i++) {
        Platform& platform = platforms.at(i);
        Position after_pos = (Position){.x = position.x + vel_x, .y = position.y + vel_y};

        if (platform.is_touching_ceiling(position)) {
            vel_y = std::min(vel_y, 0);
        } else if (platform.is_below(position) && (platform.is_above(after_pos) || platform.is_inside(after_pos))) {
            vel_y = 0;

            while (!platform.is_touching_ceiling(position))
                position.y++;
        } else if (platform.is_above(position) && (platform.is_below(after_pos) || platform.is_inside(after_pos))) {
            vel_y = 0;

            while (platform.is_inside(position))
                position.y--;
        }

        if (platform.is_inside(after_pos)) {
            vel_x = 0;

            if (position.x <= platform.get_position().x)
                position.x = platform.get_position().x - 1;
            else if (position.x >= platform.get_ur().x)
                position.x = platform.get_ur().x + 1;
        }
    }
}

void Player::clamp_speed_based_on_walls() {
    if (has_wall_on_left() && vel_x < 0)
        vel_x = 0;
    else if (has_wall_on_right() && vel_x > 0)
        vel_x = 0;
}

void Player::tick() {
    Position cur_pos = position;

    process_input();
    apply_gravity();
    clamp_velocity();
    clamp_speed_based_on_platforms();
    // clamp_speed_based_on_walls();
    move_based_on_vel();
    clamp_position();

    last_position = cur_pos;
}
