#include "player.hpp"

#include <iostream>

#include "../shared/functions.hpp"

Player::Player(GameTimer& timer, InputManager& input_manager, Level& cur_level, Position position) : game_timer(timer), input_manager(input_manager), cur_level(cur_level), position(position), vel_x(0), vel_y(0), is_jumping(false), is_running(false), is_shooting(false) {
}

void Player::move_left() {
    mvprintw(10, 10, "MOVE_LEFT");  // TODO debug
    vel_x = -1;
}

void Player::move_right() {
    mvprintw(10, 10, "MOVE_RIGHT");  // TODO debug
    vel_x = 1;
}

void Player::jump() {
    if (!is_jumping) {
        is_jumping = true;
        jump_phase = PlayerJumpPhase::Up1;
    };
}

void Player::initialize_keybindings() {
    key_bindings.push({'w', PlayerAction::Jump});
    key_bindings.push({'a', PlayerAction::MoveLeft});
    key_bindings.push({'d', PlayerAction::MoveRight});
    key_bindings.push({'^', PlayerAction::Run});
    key_bindings.push({' ', PlayerAction::Shoot});
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
    };

    int _jump_phase = ((int)jump_phase + 1);

    if (_jump_phase < jumpPhasesNum)
        jump_phase = (PlayerJumpPhase)_jump_phase;
    else
        is_jumping = false;
}

void Player::process_input() {
    for (const auto& binding : key_bindings) {
        handle_action(binding.data.action, input_manager.is_key_pressed(binding.data.key));
    }
}

void Player::handle_action(PlayerAction action, bool is_pressed) {
    if (is_pressed) {
        if (action == PlayerAction::MoveLeft)
            move_left();
        else if (action == PlayerAction::MoveRight)
            move_right();

        if (action == PlayerAction::Jump)
            jump();

        if (action == PlayerAction::Shoot)
            shoot();
    }

    if (action == PlayerAction::Run) {
        if (is_pressed)
            start_running();
        else
            stop_running();
    }
}

void Player::start_running() {
    if (is_running) return;

    is_running = true;
    vel_x *= 2;
}

void Player::stop_running() {
    if (!is_running) return;

    is_running = false;
    vel_x /= 2;
}

void Player::shoot() {
    is_shooting = true;

    // TODO
}

void Player::clamp_speed() {
    vel_x = clamp(vel_x, -2, 2);
    vel_y = clamp(vel_y, 0, 2);
}

bool Player::is_on_floor() {
    return position.y + 1 == cur_level.get_cur_room().get_floor_at(position.x);
}

bool Player::is_touching_ceiling() {
    return position.y - 1 == cur_level.get_cur_room().get_ceiling_at(position.x);
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

    position.x += vel_x * delta_time;
    position.y += vel_y * delta_time;
    position.y = std::max(position.y, cur_level.get_cur_room().get_floor_at(position.x));
}

void Player::tick() {
    process_input();
    apply_gravity();
    clamp_speed();  // TODO clampa la velocità (se is_on_floor o is_touching_ceiling ad esempio)!
    move_based_on_speed();
}

Position Player::get_position() {
    return position;
}