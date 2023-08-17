#include <iostream>

#include "asciiart/texts.hpp"
#include "gamerenderer/gamerenderer.hpp"
#include "gametimer/gametimer.hpp"
#include "list/list.hpp"
#include "list/list2d.hpp"
#include "player/player.hpp"

int main() {
    // Inizializzazione di NCurses e altre operazioni di avvio del gioco

    GameTimer game_timer;
    InputManager input_manager;

    Player player(game_timer, input_manager, (Position){.x = 10, .y = 10});

    GameRenderer game_renderer(player);

    game_timer.start();
    game_renderer.initialize();

    bool quit = false;  // TODO debug

    game_renderer.render_char_2darray(title, Alignment::Center, Alignment::Center);

    // Inizio del ciclo di gioco
    while (!quit) {
        // Chiamata a game_timer.tick() all'inizio di ogni tick
        if (game_timer.should_tick()) {
            input_manager.process_input();

            game_timer.tick();
            player.tick();
            game_renderer.render();

            game_timer.reset_accumulator();

            quit = input_manager.is_key_pressed('q');
        };

        game_timer.tick();
    }

    // Pulizia e chiusura del gioco
    // ...

    return 0;
}