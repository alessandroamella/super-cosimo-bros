#ifndef _PLAYER_HPP_
#define _PLAYER_HPP_

#include <ncurses.h>

#include "../gametimer/gametimer.hpp"
#include "../inputmanager/inputmanager.hpp"
#include "../levelmanager/levelmanager.hpp"
#include "../list/list.hpp"
#include "../shared/position.hpp"
#include "../shared/settings.hpp"

class Player {
   private:
    enum class PlayerJumpPhase {
        Up1 = 0,    // salta in alto 1^ volta
        Up2 = 1,    // salta in alto 2^ volta
        Stall = 2,  // stallo a mezzaria
        // a cadere ci pensa la gravita'
    };
    const short jumpPhasesNum = 3;

    GameTimer& game_timer;
    InputManager& input_manager;

    enum class PlayerControls {
        Jump = (int)' ',
        WalkLeft = (int)'a',
        WalkRight = (int)'d',
        RunLeft = 1,   // CTRL + A = 1
        RunRight = 4,  // CTRL + S = 4
        Shoot = (int)'e'
    };

    void update_jump_position();
    void process_input();
    void apply_gravity();
    void move_based_on_speed();
    void clamp_speed();

    void move_left();
    void move_right();
    void stop_moving();
    void run_left();
    void run_right();
    void jump();
    void shoot();
    void clamp_position();

    int health;

   public:
    Player(GameTimer& timer, InputManager& input_manager, LevelManager& cur_level,
           Position position);

    /**
     * Inizia un salto del giocatore
     *
     * Il salto è suddiviso in cinque fasi (PlayerJumpPhase):
     * `JUMP_UP_1` e `JUMP_UP_2`: salto in alto
     * `JUMP_STALL`: breve pausa in cima al salto
     * `JUMP_DOWN_1` e `JUMP_DOWN_2`: caduta
     *
     * L'incremento della fase e la modifica della posizione sono gestite
     * internamente dal metodo `update_jump_position`
     */
    Position get_position();
    Position get_last_position();
    void tick();

    // TODO finito il debug, sposta in private
    bool is_on_floor();
    bool is_touching_ceiling();
    bool has_wall_on_left();
    bool has_wall_on_right();
    int vel_x;
    int vel_y;
    Position last_position;
    Position position;
    bool is_jumping;
    bool is_shooting;
    PlayerJumpPhase jump_phase;
    LevelManager& cur_level;
};

#endif  // _PLAYER_HPP_
