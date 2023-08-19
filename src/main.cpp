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
    GameTimer game_timer(TICK_INTERVAL);
    InputManager input_manager;

    // Test level
    List<int> floor;
    for (int i = 0; i < GAME_WIDTH - 50; i++) {
        floor.push(2);
    }
    for (int i = GAME_WIDTH - 50; i < GAME_WIDTH - 20; i++) {
        floor.push(5);
    }
    for (int i = GAME_WIDTH - 20; i < GAME_WIDTH; i++) {
        floor.push(7);
    }
    Room test_room(floor, GAME_WIDTH, GAME_HEIGHT);

    List<Room> rooms;
    rooms.push(test_room);

    LevelManager level(rooms);
    Player player(game_timer, input_manager, level, (Position){.x = 10, .y = 10});
    GameRenderer game_renderer(player, level, game_timer, input_manager);

    game_timer.start();
    game_renderer.initialize();

    bool quit = false;  // TODO debug

    game_renderer.render_2d_char_array(title, Alignment::Center, Alignment::Center);

    game_renderer.wait_for_btn(' ');
    game_renderer.clear_screen();

    while (!quit) {
        input_manager.read_input();

        if (game_timer.should_tick()) {
            player.tick();
            game_renderer.render();

            quit = input_manager.is_key_pressed(QUIT_KEY);
            input_manager.clear_input_buff();
        }
    }

    return 0;
}