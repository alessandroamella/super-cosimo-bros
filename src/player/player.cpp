#include "player.hpp"

#include <iostream>
#include <string>  // TODO debug

#include "../shared/functions.hpp"

Player::Player(GameTimer& timer,
               InputManager& input_manager,
               Position position,
               List<int> floor,
               List<int> ceiling)
    : RigidEntity(timer, position, floor, ceiling),
      input_manager(input_manager),
      is_jumping(false),
      is_shooting(false),
      health(PLAYER_STARTING_HEALTH) {}

void Player::run_left() {
    vel_x = -5;
}

void Player::run_right() {
    vel_x = 5;
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
        case PlayerJumpPhase::Up1:
        case PlayerJumpPhase::Up2:
            vel_y += PLAYER_JUMP_VEL;
            break;
        case PlayerJumpPhase::Stall:
            vel_y = 0;
            break;
    };

    int _jump_phase = ((int)jump_phase + 1);

    if (_jump_phase < jumpPhasesNum)
        jump_phase = (PlayerJumpPhase)_jump_phase;
    else
        is_jumping = false;
}

void Player::process_input() {
    if (input_manager.is_key_pressed((int)PlayerControls::Jump) && is_on_floor())
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

// override: controlla se sta saltando
void Player::apply_gravity() {
    if (is_jumping)
        update_jump_position();
    else if (is_on_floor())
        vel_y = 0;
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

void Player::tick() {
    Position cur_pos = position;

    process_input();
    apply_gravity();
    clamp_velocity();
    move_based_on_vel();
    clamp_position();

    last_position = cur_pos;
}
