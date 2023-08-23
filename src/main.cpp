#include <iostream>

#include "./shared/functions.hpp"
#include "asciiart/texts.hpp"
#include "gamerenderer/gamerenderer.hpp"
#include "gametimer/gametimer.hpp"
#include "hitbox/hitbox.hpp"
#include "levelmanager/levelmanager.hpp"
#include "list/list.hpp"
#include "list/list2d.hpp"
#include "mushroom/mushroom.hpp"
#include "player/player.hpp"
#include "powerup/powerup.hpp"
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
        floor.push(3);
    }

    List<int> ceiling;
    for (int i = 0; i < GAME_WIDTH; i++) {
        ceiling.push(GAME_HEIGHT - 1);
    }

    // generate platform
    List<Platform> platforms;

    Platform _platform1((Position){.x = 111, .y = 9}, (Position){.x = 120, .y = 12});
    Platform _platform2((Position){.x = 60, .y = 10}, (Position){.x = 78, .y = 12});
    Platform _platform3((Position){.x = 65, .y = 15}, (Position){.x = 69, .y = 19});
    Platform _platform4((Position){.x = 40, .y = 20}, (Position){.x = 57, .y = 23});

    platforms.push(_platform1);
    platforms.push(_platform2);
    platforms.push(_platform3);
    platforms.push(_platform4);

    List<Powerup> powerups;
    powerups.push(Mushroom((Position){.x = 20, .y = 10}));
    powerups.push(Mushroom((Position){.x = 42, .y = 29}));

    Room test_room(powerups, floor, ceiling, platforms, GAME_WIDTH, GAME_HEIGHT);

    List<Room> rooms;
    rooms.push(test_room);

    LevelManager level(&rooms, game_timer);
    Player player(game_timer, input_manager, (Position){.x = 10, .y = 10}, test_room.get_floor(), test_room.get_ceiling(), platforms, powerups);
    GameRenderer game_renderer(player, level, game_timer, input_manager);

    game_timer.start();
    game_renderer.initialize();

    bool quit = false;  // TODO debug

    game_renderer.render_2d_char_array(title, Alignment::Center, Alignment::Center);

    game_renderer.wait_for_btn(' ');
    game_renderer.clear_screen();

    level.place_enemies_randomly(2, 10);
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

                if (collides(player, enemy) && !enemy.get_is_dead()) {
                    if (player.get_has_powerup()) {
                        switch (player.get_powerup_type()) {
                            case EntityType::Mushroom:
                                player.set_has_powerup(false);
                                break;
                            case EntityType::Star:
                                enemy.set_is_dead(true);
                                break;
                        }
                    } else {
                        player.remove_health(ENEMY_DAMAGE);
                        player.jump();
                    }
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