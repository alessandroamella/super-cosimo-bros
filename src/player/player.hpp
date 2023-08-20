#ifndef _PLAYER_HPP_
#define _PLAYER_HPP_

#include <ncurses.h>

#include "../gametimer/gametimer.hpp"
#include "../inputmanager/inputmanager.hpp"
#include "../list/list.hpp"
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

    int health;

    void update_jump_position();
    void process_input();

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
           List<int> ceiling);

    bool is_jumping;
    bool is_shooting;
    PlayerJumpPhase jump_phase;

    void jump();

    int get_health();
    void add_health(int amount);
    void set_health(int amount);
    void remove_health(int amount);

    // overrides
    void tick();
};

#endif  // _PLAYER_HPP_
