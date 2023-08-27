#ifndef _PLAYER_HPP_
#define _PLAYER_HPP_

#include <ncurses.h>

#include "../gametimer/gametimer.hpp"
#include "../inputmanager/inputmanager.hpp"
#include "../list/list.hpp"
#include "../platform/platform.hpp"
#include "../powerup/powerup.hpp"
#include "../rigidentity/rigidentity.hpp"
#include "../shared/position.hpp"
#include "../shared/settings.hpp"

class Player : public RigidEntity {
   private:
    const short jumpPhasesNum = 3;

    InputManager* input_manager;

    List<Powerup*>* powerups;

    int health;
    int coins;

    bool is_damaged;
    int damaged_ticks;

    EntityType powerup_type;

    void update_jump_position();
    void process_input();

    void handle_platform_collisions();
    void handle_powerup_collisions();
    void handle_wall_collisions();

    void run_left();
    void run_right();
    void shoot();

    int star_ticks;
    std::chrono::steady_clock::time_point star_expires_at;
    void tick_star();

    void apply_gravity();

    std::chrono::steady_clock::time_point next_projectile_delay;

   public:
    Player(GameTimer* timer,
           InputManager* input_manager,
           Position position,
           List<int>* floor,
           List<int>* ceiling,
           List<Platform>* platforms,
           List<Powerup*>* powerups);

    bool is_jumping;
    bool is_shooting;
    PlayerJumpPhase jump_phase;

    void jump();

    int get_health();
    void add_health(int amount);
    void set_health(int amount);
    void remove_health(int amount);

    int get_coins();
    int* get_coins_ptr();
    void add_coins(int amount);
    void remove_coins(int amount);

    bool get_has_powerup();
    EntityType get_powerup_type();
    void set_powerup_type(EntityType powerup_type);
    EntityType* get_powerup_type_ptr();
    void remove_powerup();

    bool get_is_damaged();
    void set_is_damaged(bool is_damaged);
    bool damaged_should_tick();

    bool has_star();
    bool should_show_star();
    void add_star();

    bool should_shoot();
    void reset_shoot();

    void refresh(Position position,
                 List<int>* floor,
                 List<int>* ceiling,
                 List<Platform>* platforms,
                 List<Powerup*>* powerups);

    void tick();
};

#endif  // _PLAYER_HPP_
