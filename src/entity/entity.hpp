#ifndef _ENTITY_HPP_
#define _ENTITY_HPP_

#include <ncurses.h>

#include "../gametimer/gametimer.hpp"
#include "../inputmanager/inputmanager.hpp"
#include "../levelmanager/levelmanager.hpp"
#include "../list/list.hpp"
#include "../shared/position.hpp"
#include "../shared/settings.hpp"

class Entity {
   private:
    GameTimer& game_timer;

    void apply_gravity();
    void move_based_on_speed();
    void clamp_speed();

    void move_left();
    void move_right();
    void stop_moving();
    void run_left();
    void run_right();
    void shoot();
    void clamp_position();

    int health;

   public:
    Entity(GameTimer& timer, InputManager& input_manager,
           LevelManager& cur_level, Position position);

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

#endif  // _ENTITY_HPP_
