#include <iostream>

#include "asciiart/texts.hpp"
#include "gamerenderer/gamerenderer.hpp"
#include "gametimer/gametimer.hpp"
#include "levelmanager/levelmanager.hpp"
#include "list/list.hpp"
#include "list/list2d.hpp"
#include "player/player.hpp"
#include "room/room.hpp"

int main() {
    // Istanzio classi del gioco
    GameTimer game_timer;
    InputManager input_manager;

    List<int> floor;
    for (int i = 0; i < GAME_WIDTH - 50; i++) {
        floor.push(2);
    }
    for (int i = GAME_WIDTH - 50; i < GAME_WIDTH - 20; i++) {
        floor.push(5);
    }
    for (int i = GAME_WIDTH - 20; i < GAME_WIDTH; i++) {
        floor.push(10);
    }
    Room test_room(floor);

    List<Room> rooms;
    rooms.push(test_room);
    LevelManager level(rooms);

    Player player(game_timer, input_manager, level,
                  (Position){.x = 10, .y = 10});

    GameRenderer game_renderer(player, level, game_timer, input_manager);

    // Avvio timer, initializzo ncurses
    game_timer.start();
    game_renderer.initialize();

    bool quit = false;  // TODO debug

    game_renderer.render_2d_char_array(title, Alignment::Center,
                                       Alignment::Center);

    game_renderer.wait_for_btn(' ');
    game_renderer.clear_screen();

    // Inizio del ciclo di gioco
    while (!quit) {
        if (game_timer.should_tick()) {
            input_manager.read_input();

            game_timer.tick();
            player.tick();
            game_renderer.render();

            game_timer.reset_accumulator();

            quit = input_manager.is_key_pressed(QUIT_KEY);
        };

        game_timer.tick();
    }

    return 0;
}