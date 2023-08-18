#include <iostream>

#include "asciiart/texts.hpp"
#include "gamerenderer/gamerenderer.hpp"
#include "gametimer/gametimer.hpp"
#include "level/level.hpp"
#include "list/list.hpp"
#include "list/list2d.hpp"
#include "player/player.hpp"
#include "room/room.hpp"

int main() {
    // Istanzio classi del gioco
    GameTimer game_timer;
    InputManager input_manager;

    int floor[GAME_WIDTH];
    for (int i = 0; i < GAME_WIDTH - 100; i++) {
        floor[i] = 2;
    }
    for (int i = GAME_WIDTH - 100; i < GAME_WIDTH - 30; i++) {
        floor[i] = 5;
    }
    for (int i = GAME_WIDTH - 30; i < GAME_WIDTH; i++) {
        floor[i] = 10;
    }
    Room test_room(floor);

    List<Room> rooms;
    rooms.push(test_room);
    Level level(rooms, "ciaone");

    Player player(game_timer, input_manager, level, (Position){.x = 10, .y = 10});

    GameRenderer game_renderer(player, level, game_timer);

    // Avvio timer, initializzo ncurses
    game_timer.start();
    game_renderer.initialize();

    bool quit = false;  // TODO debug

    game_renderer.render_2d_char_array(title, Alignment::Center, Alignment::Center);

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

            quit = input_manager.is_key_pressed('q');

            // DEBUG PRINT
            game_renderer.render_str_num((Position){.x = 0, .y = 1}, "TICKS", (int)game_timer.get_delta_time_sec());
        };

        game_timer.tick();
    }

    // Pulizia e chiusura del gioco
    // ...

    return 0;
}