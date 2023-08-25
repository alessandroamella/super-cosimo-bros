#ifndef _GAMEMANAGER_HPP_
#define _GAMEMANAGER_HPP_

#include <iostream>

#include "../asciiart/texts.hpp"
#include "../gamerenderer/gamerenderer.hpp"
#include "../gametimer/gametimer.hpp"
#include "../hitbox/hitbox.hpp"
#include "../levelmanager/levelmanager.hpp"
#include "../list/list.hpp"
#include "../list/list2d.hpp"
#include "../maps/maps.hpp"
#include "../mushroom/mushroom.hpp"
#include "../player/player.hpp"
#include "../powerup/powerup.hpp"
#include "../room/room.hpp"
#include "../shared/functions.hpp"

class GameManager {
   private:
    GameTimer game_timer;
    InputManager input_manager;

    Maps game_maps;
    List<Room> rooms;
    List<Powerup*> powerups;

    LevelManager* level;
    Player* player;
    GameRenderer* game_renderer;

    AsciiTexts ascii_texts;

    void splash_screen();
    void tick_all();
    void handle_enemy_collisions();
    void game_over_screen();
    void main_loop();

   public:
    GameManager();
    void begin();
};

#endif  // _GAMEMANAGER_HPP_