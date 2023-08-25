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
    enum class PlayerJumpPhase {
        Up1 = 0,    // salta in alto 1^ volta
        Up2 = 1,    // salta in alto 2^ volta
        Stall = 2,  // stallo a mezzaria
    };
    const short jumpPhasesNum = 3;

    enum class PlayerControls {
        Jump = (int)' ',
        WalkLeft = (int)'a',
        WalkRight = (int)'d',
        RunLeft = 1,   // CTRL + A = 1
        RunRight = 4,  // CTRL + S = 4
        Shoot = (int)'e'
    };

    InputManager& input_manager;

    List<Powerup*>& powerups;

    int health;
    int coins;

    bool is_damaged;
    int damaged_ticks;

    bool has_powerup;
    EntityType powerup_type;

    void update_jump_position();
    void process_input();

    void handle_platform_collisions();
    void handle_powerup_collisions();
    void handle_wall_collisions();

    void run_left();
    void run_right();
    void shoot();

    // overrides
    void apply_gravity();

   public:
    Player(GameTimer& timer,
           InputManager& input_manager,
           Position position,
           List<int> floor,
           List<int> ceiling,
           List<Platform>& platforms,
           List<Powerup*>& powerups);

    bool is_jumping;
    bool is_shooting;
    PlayerJumpPhase jump_phase;

    void jump();

    int get_health();
    void add_health(int amount);
    void set_health(int amount);
    void remove_health(int amount);

    int get_coins();
    void add_coins(int amount);
    void remove_coins(int amount);

    bool get_has_powerup();
    EntityType get_powerup_type();
    void set_has_powerup(bool has_powerup);

    bool get_is_damaged();
    void set_is_damaged(bool is_damaged);
    bool damaged_should_tick();

    void refresh(Position position,
                 List<int> floor,
                 List<int> ceiling,
                 List<Platform>& platforms,
                 List<Powerup*>& powerups);

    void tick();
};

#endif  // _PLAYER_HPP_
