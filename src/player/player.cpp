#include "player.hpp"

#include <iostream>

#include "../coin/coin.hpp"
#include "../mushroom/mushroom.hpp"
#include "../shared/functions.hpp"
#include "../star/star.hpp"

Player::Player(GameTimer& timer,
               InputManager& input_manager,
               Position position,
               List<int> floor,
               List<int> ceiling,
               List<Platform>& platforms,
               List<Powerup*>& powerups)
    : RigidEntity(timer, position, floor, ceiling, platforms),
      input_manager(input_manager),
      is_jumping(false),
      is_shooting(false),
      has_powerup(false),
      health(PLAYER_STARTING_HEALTH),
      coins(0),
      powerups(powerups),
      is_damaged(false),
      damaged_ticks(0) {}

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
    if (is_damaged && damaged_should_tick())
        return std::min(health, 1);

    if (health <= 0)
        set_is_damaged(false);

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

bool Player::get_has_powerup() {
    return has_powerup;
}

void Player::set_has_powerup(bool _has_powerup) {
    has_powerup = _has_powerup;
}

bool Player::get_is_damaged() {
    if (!is_damaged)
        return false;

    damaged_ticks++;
    if (damaged_ticks > PLAYER_DAMAGED_TOTAL_TICKS)
        is_damaged = false;

    return is_damaged;
}

void Player::set_is_damaged(bool _is_damaged) {
    is_damaged = _is_damaged;
    damaged_ticks = 0;
}

bool Player::damaged_should_tick() {
    return damaged_ticks % PLAYER_DAMAGED_BLINK_TICKS == 0;
}

void Player::refresh(Position _position, List<int> _floor, List<int> _ceiling, List<Platform>& _platforms, List<Powerup*>& _powerups) {
    position = _position;
    floor = _floor;
    ceiling = _ceiling;
    platforms = _platforms;
    powerups = _powerups;
}

EntityType Player::get_powerup_type() {
    return powerup_type;
}

int Player::get_coins() {
    return coins;
}

void Player::add_coins(int amount) {
    coins += amount;
}

void Player::remove_coins(int amount) {
    coins = std::max(coins - amount, 0);
}

void Player::handle_platform_collisions() {
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

void Player::handle_powerup_collisions() {
    for (int i = 0; i < powerups.length(); i++) {
        // giusto per stare sicuri
        if (powerups.at(i) == nullptr)
            throw std::runtime_error("Null pointer exception at Player::handle_powerup_collisions()");

        Powerup* powerup = powerups.at(i);
        // check null pointer

        Position after_pos = (Position){.x = position.x + vel_x, .y = position.y + vel_y};

        if (powerup->is_inside(after_pos) || (powerup->is_below(position) && (powerup->is_above(after_pos) || powerup->is_inside(after_pos))) || (powerup->is_above(position) && (powerup->is_below(after_pos) || powerup->is_inside(after_pos)))) {
            switch (powerup->get_entity_type()) {
                case EntityType::Mushroom:
                    has_powerup = has_powerup || powerup->get_is_active();
                    powerup_type = powerup->get_entity_type();
                    break;
                case EntityType::Star:
                    has_powerup = has_powerup || powerup->get_is_active();
                    powerup_type = powerup->get_entity_type();
                    break;
                case EntityType::Heart:
                    add_health(HEART_HEALTH_INCREASE);
                    break;
                case EntityType::Coin:
                    Coin* coinPowerup = dynamic_cast<Coin*>(powerup);
                    if (coinPowerup) {
                        int coin_value = coinPowerup->get_value();
                        add_coins(coin_value);
                    }
                    break;
            }

            powerup->set_is_active(false);
        }
    }
}

void Player::handle_wall_collisions() {
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
    handle_platform_collisions();
    handle_powerup_collisions();
    move_based_on_vel();
    clamp_position();

    last_position = cur_pos;
}
