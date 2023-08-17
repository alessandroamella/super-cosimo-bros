#ifndef _PLAYER_HPP_
#define _PLAYER_HPP_

#include <ncurses.h>

#include "../gametimer/gametimer.hpp"
#include "../inputmanager/inputmanager.hpp"
#include "../list/list.hpp"
#include "../shared/position.hpp"
#include "../shared/settings.hpp"

class Player {
   private:
    enum class PlayerJumpPhase {
        Up1 = 0,    // salta in alto 1^ volta
        Up2 = 1,    // salta in alto 2^ volta
        Stall = 2,  // stallo a mezzaria
        Down1 = 3,  // ricadi giù 1^ volta
        Down2 = 4,  // ricadi giù 2^ volta
    };
    const short jumpPhasesNum = 5;

    enum class PlayerAction {
        Jump,
        MoveLeft,
        MoveRight,
        Crouch,
        Run,
        Shoot
    };

    struct PlayerKeyBinding {
        char key;
        PlayerAction action;
    };

    List<PlayerKeyBinding> key_bindings;

    GameTimer& game_timer;
    InputManager& input_manager;

    Position position;

    int vel_x;
    int vel_y;

    bool is_jumping;

    bool is_running;
    bool is_shooting;
    bool is_crouching;

    PlayerJumpPhase jump_phase;

    void initialize_keybindings();
    void update_jump_position();
    void process_input();
    void handle_action(PlayerAction action);

   public:
    Player(GameTimer& timer, InputManager& input_manager, Position position);

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
    Position get_position();
};

#endif  // _PLAYER_HPP_
