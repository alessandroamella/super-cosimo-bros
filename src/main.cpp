#include <iostream>

#include "gametimer/gametimer.hpp"
#include "list/list.hpp"
#include "list/list2d.hpp"
#include "player/player.hpp"

const int DEBUG_QUIT = false;  // TODO di debug

int main() {
    // Inizializzazione di NCurses e altre operazioni di avvio del gioco

    GameTimer game_timer;
    InputManager input_manager;

    game_timer.start();

    Player player(game_timer, input_manager, 0, 0);

    // Inizio del ciclo di gioco
    while (!DEBUG_QUIT) {
        // Chiamata a game_timer.tick() all'inizio di ogni tick
        if (game_timer.should_tick()) {
            input_manager.process_input();

            game_timer.tick();
            player.tick();

            game_timer.reset_accumulator();
        };

        game_timer.tick();
    }

    // Pulizia e chiusura del gioco
    // ...

    return 0;
}