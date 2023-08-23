#include <iostream>

#include "./shared/functions.hpp"
#include "asciiart/texts.hpp"
#include "gamerenderer/gamerenderer.hpp"
#include "gametimer/gametimer.hpp"
#include "hitbox/hitbox.hpp"
#include "levelmanager/levelmanager.hpp"
#include "list/list.hpp"
#include "list/list2d.hpp"
#include "player/player.hpp"
#include "room/room.hpp"
#include "maps/maps.hpp"

int main() {
    GameTimer game_timer(TICK_INTERVAL);
    InputManager input_manager;

    Maps game_maps;
    Room layout_1 = game_maps.layout1(game_timer);
    Room layout_2 = game_maps.layout2(game_timer);
    Room layout_3 = game_maps.layout3(game_timer);

    List<Room> rooms;
    rooms.push(layout_3);

    LevelManager level(&rooms);
    Player player(game_timer, input_manager, (Position){.x = 10, .y = 10}, level.get_cur_room()->get_floor(), level.get_cur_room()->get_floor(), level.get_cur_room()->get_platforms());
    GameRenderer game_renderer(player, level, game_timer, input_manager);

    game_timer.start();
    game_renderer.initialize();

    bool quit = false;  // TODO debug

    game_renderer.render_2d_char_array(title, Alignment::Center, Alignment::Center);

    game_renderer.wait_for_btn(' ');
    game_renderer.clear_screen();

    level.get_cur_room()->place_enemies_randomly(2, 10);
    level.get_cur_room()->load();

    while (!quit) {
        input_manager.read_input();

        if (game_timer.should_tick()) {
            player.tick();
            level.tick();
            game_renderer.render_all();

            // TODO delega una classe esterna
            for (size_t i = 0; i < level.get_cur_room()->get_enemies().length(); i++) {
                Enemy& enemy = level.get_cur_room()->get_enemies().at(i);

                if (collides(player, enemy)) {
                    player.remove_health(ENEMY_DAMAGE);
                    player.jump();
                }
            }

            if (player.get_health() <= 0) {
                game_renderer.render_2d_char_array(game_over, Alignment::Center, Alignment::Center);
                game_renderer.wait_for_btn(' ');
                game_renderer.clear_screen();
                player.set_health(PLAYER_STARTING_HEALTH);
                player.reset_position();
                level.get_cur_room()->load();
            }

            quit = input_manager.is_key_pressed(QUIT_KEY);
            input_manager.clear_input_buff();
        }
    }

    return 0;
}