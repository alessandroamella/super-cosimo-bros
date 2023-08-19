#ifndef _PLAYER_HPP_
#define _PLAYER_HPP_

#include <ncurses.h>

#include "../gametimer/gametimer.hpp"
#include "../inputmanager/inputmanager.hpp"
#include "../levelmanager/levelmanager.hpp"
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

    void update_jump_position();
    void process_input();

    void run_left();
    void run_right();
    void jump();
    void shoot();

    // overrides
    void apply_gravity();

   public:
    Player(GameTimer& timer,
           InputManager& input_manager,
           LevelManager& cur_level,
           Position position);

    int health;
    bool is_jumping;
    bool is_shooting;
    PlayerJumpPhase jump_phase;

    // overrides
    void tick();
};

#endif  // _PLAYER_HPP_
