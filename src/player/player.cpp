#include "player.hpp"

#include <iostream>

Player::Player(GameTimer& timer, InputManager& input_manager, int start_x, int start_y) : game_timer(timer), input_manager(input_manager), x(start_x), y(start_y), vel_x(0), vel_y(0), is_jumping(false), is_running(false), is_shooting(false), is_crouching(false) {
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
        jump_phase = JUMP_UP_1;
    };
}

void Player::update_jump_position() {
    // TODO controlla se sul pavimento

    switch (jump_phase) {
        case JUMP_UP_1:
        case JUMP_UP_2:
            vel_y += PLAYER_JUMP_VEL;
            break;
        case JUMP_STALL:
            vel_y = 0;
        case JUMP_DOWN_1:
        case JUMP_DOWN_2:
            vel_y -= PLAYER_JUMP_VEL;
            break;
    };

    int _jump_phase = ((int)jump_phase + 1);

    if (_jump_phase < JUMP_PHASES_NUM)
        jump_phase = (PlayerJumpPhase)_jump_phase;
    else
        is_jumping = false;
}

void Player::process_input() {
    if (input_manager.is_key_pressed('w')) {
        jump();
    }
    if (input_manager.is_key_pressed('a')) {
        move_left();
    }
    if (input_manager.is_key_pressed('d')) {
        move_right();
    }
    if (input_manager.is_key_pressed(KEY_SLEFT)) {
        crouch();
    }
    if (input_manager.is_key_pressed('^')) {  // TODO non funge
        run();
    }
    if (input_manager.is_key_pressed(' ')) {
        shoot();
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

bool s = 0;

void Player::tick() {
    float delta_time = game_timer.get_delta_time_sec();

    x += vel_x * delta_time;
    y += vel_y * delta_time;

    update_jump_position();
    std::cout << delta_time << std::endl;

    // TODO clampa la velocità (se is_on_floor o is_touching_ceiling ad esempio)!
}

void Player::render() {
    mvprintw(y, x, "@");
    // refresh(); da chiamare nel main

    // TODO
}
