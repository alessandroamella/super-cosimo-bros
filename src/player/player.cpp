#include "player.hpp"

#include <iostream>

Player::Player(GameTimer& timer, InputManager& input_manager, Position position) : game_timer(timer), input_manager(input_manager), position(position), vel_x(0), vel_y(0), is_jumping(false), is_running(false), is_shooting(false), is_crouching(false) {
}

void Player::move_left() {
    vel_x = -1;
}

void Player::move_right() {
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
    key_bindings.push({(char)KEY_SLEFT, PlayerAction::Crouch});
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
        case PlayerJumpPhase::Down1:
        case PlayerJumpPhase::Down2:
            vel_y -= PLAYER_JUMP_VEL;
            break;
    };

    int _jump_phase = ((int)jump_phase + 1);

    if (_jump_phase < jumpPhasesNum)
        jump_phase = (PlayerJumpPhase)_jump_phase;
    else
        is_jumping = false;
}

void Player::process_input() {
    for (const auto& binding : key_bindings) {
        if (input_manager.is_key_pressed(binding.data.key)) {
            handle_action(binding.data.action);
        }
    }
}

void Player::handle_action(PlayerAction action) {
    switch (action) {
        case PlayerAction::Jump:
            jump();
            break;
        case PlayerAction::MoveLeft:
            move_left();
            break;
        case PlayerAction::MoveRight:
            move_right();
            break;
        case PlayerAction::Crouch:
            crouch();
            break;
        case PlayerAction::Run:
            run();
            break;
        case PlayerAction::Shoot:
            shoot();
            break;
    }
}

void Player::run() {
    if (is_running) return;

    is_running = true;
    vel_x *= 2;
}

void Player::shoot() {
    is_shooting = true;

    // TODO
}

void Player::crouch() {
    is_crouching = true;

    // TODO
}

void Player::tick() {
    float delta_time = game_timer.get_delta_time_sec();

    position.x += vel_x * delta_time;
    position.y += vel_y * delta_time;

    update_jump_position();

    // TODO clampa la velocità (se is_on_floor o is_touching_ceiling ad esempio)!
}

Position Player::get_position() {
    return position;
}