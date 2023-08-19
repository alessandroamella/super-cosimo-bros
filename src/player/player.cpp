#include "player.hpp"

#include <iostream>
#include <string>  // TODO debug

#include "../shared/functions.hpp"

Player::Player(GameTimer& timer, InputManager& input_manager, Level& cur_level, Position position) : game_timer(timer), input_manager(input_manager), cur_level(cur_level), position(position), last_position(position), vel_x(0), vel_y(0), is_jumping(false), is_shooting(false) {
}

void Player::move_left() {
    vel_x = -1;
}

void Player::move_right() {
    vel_x = 1;
}

void Player::run_left() {
    vel_x = -2;
}

void Player::run_right() {
    vel_x = 2;
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
    else
        stop_moving();

    if (input_manager.is_key_pressed((int)PlayerControls::Shoot))
        shoot();

    // for (int i = 0; i < key_bindings.length(); i++) {
    //     handle_action(key_bindings.at(i).action, input_manager.is_key_pressed(key_bindings.at(i).key));
    // }
}

void Player::stop_moving() {
    vel_x = 0;
}

void Player::shoot() {
    is_shooting = true;

    // TODO
}

void Player::clamp_speed() {
    vel_x = clamp(vel_x, -2, 2);
    vel_y = clamp(vel_y, -1, 2);
}

bool Player::is_on_floor() {
    return position.y - 2 <= cur_level.get_cur_room().get_floor_at(position.x);
}

bool Player::is_touching_ceiling() {
    return position.y - 1 >= cur_level.get_cur_room().get_ceiling_at(position.x);
}

bool Player::has_wall_on_left() {
    // TODO < o <= 1?
    return position.x <= 1 || cur_level.get_cur_room().get_floor_at(position.x - 1) > position.y;
}

bool Player::has_wall_on_right() {
    // TODO < o <= 1?
    return position.x >= GAME_WIDTH || position.y < cur_level.get_cur_room().get_floor_at(position.x + 1);
}

void Player::clamp_position() {
    // x
    if (has_wall_on_left())
        position.x = 1;
    else if (has_wall_on_right())
        position.x = GAME_WIDTH - 1;

    // y
    position.y = std::max(position.y, cur_level.get_cur_room().get_floor_at(position.x) + 2);
}

void Player::apply_gravity() {
    if (is_jumping)
        update_jump_position();
    else if (!is_on_floor())
        vel_y--;

    // se tocca il soffitto, la vel_y deve essere <= 0
    if (is_touching_ceiling())
        vel_y = clamp(vel_y, vel_y, 0);
};

void Player::move_based_on_speed() {
    float delta_time = game_timer.get_delta_time_sec();

    position.x += vel_x /* * delta_time */;
    position.y += vel_y /* * delta_time */;
}

void Player::tick() {
    Position cur_pos = position;

    process_input();
    apply_gravity();
    clamp_speed();  // TODO clampa la velocità (se is_on_floor o is_touching_ceiling ad esempio)!
    clamp_position();
    move_based_on_speed();

    last_position = cur_pos;
}

Position Player::get_last_position() {
    return last_position;
}

Position Player::get_position() {
    return position;
}