#ifndef _PLAYER_HPP_
#define _PLAYER_HPP_

#include <ncurses.h>

#include "../gametimer/gametimer.hpp"
#include "../inputmanager/inputmanager.hpp"

#define PLAYER_JUMP_VEL 2;

enum PlayerJumpPhase {
    JUMP_UP_1 = 0,        // salta in alto 1^ volta
    JUMP_UP_2 = 1,        // salta in alto 2^ volta
    JUMP_STALL = 2,       // stallo a mezzaria
    JUMP_DOWN_1 = 3,      // ricadi giù 1^ volta
    JUMP_DOWN_2 = 4,      // ricadi giù 2^ volta
    JUMP_PHASES_NUM = 5,  // tot fasi
};

class Player {
   private:
    GameTimer& game_timer;
    InputManager& input_manager;

    int x, y;

    int vel_x;
    int vel_y;

    bool is_jumping;

    bool is_running;
    bool is_shooting;
    bool is_crouching;

    PlayerJumpPhase jump_phase;

    void update_jump_position();
    void process_input();

   public:
    Player(GameTimer& timer, InputManager& input_manager, int start_x, int start_y);

    void move_left();
    void move_right();

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
    void jump();
    void run();
    void shoot();
    void crouch();

    void tick();
    void render();
};

#endif  // _PLAYER_HPP_
