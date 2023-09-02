#include "player.hpp"

#include <iostream>

#include "../coin/coin.hpp"
#include "../mushroom/mushroom.hpp"
#include "../shared/functions.hpp"
#include "../star/star.hpp"

Player::Player(InputManager* input_manager,
               Position position,
               List<int>* floor,
               List<int>* ceiling,
               List<Platform>* platforms,
               List<Powerup*>* powerups)
    : RigidEntity(position, floor, ceiling, platforms),
      input_manager(input_manager),
      is_jumping(false),
      is_shooting(false),
      powerup_type(EntityType::None),
      health(PLAYER_STARTING_HEALTH),
      coins(PLAYER_STARTING_COINS),
      powerups(powerups),
      is_damaged(false),
      damaged_ticks(0),
      next_projectile_delay(std::chrono::steady_clock::now() + std::chrono::milliseconds(PROJECTILE_DELAY_MS)) {}

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
    int key_pressed = input_manager->get_last_ch();

    if (key_pressed == (int)PlayerControls::Jump && (is_on_floor() || is_on_platform()))
        jump();

    if (key_pressed == (int)PlayerControls::RunLeft)
        run_left();
    else if (key_pressed == (int)PlayerControls::WalkLeft)
        move_left();
    else if (key_pressed == (int)PlayerControls::RunRight)
        run_right();
    else if (key_pressed == (int)PlayerControls::WalkRight)
        move_right();
    else if (!is_jumping)
        apply_friction();

    if (key_pressed == (int)PlayerControls::Shoot && powerup_type == EntityType::Gun)
        shoot();
}

void Player::shoot() {
    is_shooting = true;
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
    health = std::min(health + amount, PLAYER_MAX_HEALTH);
}

void Player::set_health(int amount) {
    health = clamp(amount, 0, PLAYER_MAX_HEALTH);
}

void Player::remove_health(int amount) {
    health = std::max(health - amount, 0);
}

bool Player::get_has_powerup() {
    return powerup_type != EntityType::None;
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

bool Player::has_star() {
    return powerup_type == EntityType::Star;
}

bool Player::should_show_star() {
    return star_ticks % 2 == 0;
}

void Player::add_star() {
    star_ticks = 0;
    star_expires_at = std::chrono::steady_clock::now() + std::chrono::seconds(STAR_POWERUP_DURATION_SECONDS);
}

bool Player::should_shoot() {
    return is_shooting && std::chrono::steady_clock::now() > next_projectile_delay;
}

void Player::reset_shoot() {
    is_shooting = false;
    next_projectile_delay = std::chrono::steady_clock::now() + std::chrono::milliseconds(PROJECTILE_DELAY_MS);
}

void Player::tick_star() {
    if (!has_star())
        return;

    if (std::chrono::steady_clock::now() > star_expires_at) {
        powerup_type = EntityType::None;
        star_ticks = 0;
    } else {
        star_ticks++;
    }
}

void Player::refresh(Position position, List<int>* floor, List<int>* ceiling, List<Platform>* platforms, List<Powerup*>* powerups) {
    this->position = position;
    this->floor = floor;
    this->ceiling = ceiling;
    this->platforms = platforms;
    this->powerups = powerups;
    vel_x = 0;
    vel_y = 0;

    is_jumping = false;
    is_shooting = false;
    // powerup_type = EntityType::None;
    is_damaged = false;
    damaged_ticks = 0;
    next_projectile_delay = std::chrono::steady_clock::now() + std::chrono::milliseconds(PROJECTILE_DELAY_MS);
}

EntityType Player::get_powerup_type() {
    return powerup_type;
}

void Player::set_powerup_type(EntityType _powerup_type) {
    powerup_type = _powerup_type;
}

EntityType* Player::get_powerup_type_ptr() {
    return &powerup_type;
}

void Player::remove_powerup() {
    powerup_type = EntityType::None;
}

int Player::get_coins() {
    return coins;
}

int* Player::get_coins_ptr() {
    return &coins;
}

void Player::add_coins(int amount) {
    coins = std::min(std::max(coins + amount, 0), PLAYER_MAX_COINS);
}

void Player::remove_coins(int amount) {
    coins = std::max(coins - amount, 0);
}

void Player::handle_platform_collisions() {
    for (int i = 0; i < platforms->length(); i++) {
        Platform& platform = platforms->at(i);
        Position after_pos = get_after_pos();

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
    for (int i = 0; i < powerups->length(); i++) {
        // giusto per stare sicuri
        if (powerups->at(i) == nullptr)
            throw std::runtime_error("Null pointer exception at Player::handle_powerup_collisions()");

        Powerup* powerup = powerups->at(i);
        // check null pointer

        Position after_pos = get_after_pos();

        if (powerup->get_is_active() && (powerup->is_inside(after_pos) || (powerup->is_below(position) && (powerup->is_above(after_pos) || powerup->is_inside(after_pos))) || (powerup->is_above(position) && (powerup->is_below(after_pos) || powerup->is_inside(after_pos))))) {
            int coin_value;
            Coin* coinPowerup;

            switch (powerup->get_entity_type()) {
                case EntityType::Mushroom:
                case EntityType::Gun:
                    powerup_type = powerup->get_entity_type();
                    break;
                case EntityType::Star:
                    powerup_type = powerup->get_entity_type();
                    add_star();
                    break;
                case EntityType::Heart:
                    add_health(HEART_HEALTH_INCREASE);
                    break;
                case EntityType::Coin:
                    coinPowerup = dynamic_cast<Coin*>(powerup);
                    if (coinPowerup) {
                        coin_value = coinPowerup->get_value();
                        add_coins(coin_value);
                    }
                    break;
                default:
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

    if (has_star())
        tick_star();

    last_position = cur_pos;
}
