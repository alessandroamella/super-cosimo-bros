#include "gamemanager.hpp"

GameManager::GameManager()
    : game_timer(TICK_INTERVAL),
      input_manager(),
      game_maps(),
      ascii_texts() {
    rooms = List<Room*>();

    rooms.push(game_maps.get_room(0));
    rooms.push(game_maps.get_room(1));
    rooms.push(game_maps.get_room(2));

    powerups = List<Powerup*>();

    level = new LevelManager(&rooms, &game_timer);

    player = new Player(&game_timer, &input_manager, level->get_cur_room()->get_player_start_position(), &level->get_cur_room()->get_floor(), &level->get_cur_room()->get_ceiling(), &level->get_cur_room()->get_platforms(), &powerups);

    game_renderer = new GameRenderer(player, level, &game_timer);

    game_timer.start();
    game_renderer->initialize();
}

void GameManager::splash_screen() {
    game_renderer->render_2d_char_array(ascii_texts.get_splash(), Alignment::Center, Alignment::Center);

    input_manager.wait_for_btn(game_renderer->get_win(), ' ');
    game_renderer->clear_screen();
}

void GameManager::handle_enemy_collisions() {
    for (int i = 0; i < level->get_cur_room()->get_enemies().length(); i++) {
        Enemy& enemy = level->get_cur_room()->get_enemies().at(i);

        if (collides(player, &enemy) && !enemy.get_is_dead()) {
            if (player->get_has_powerup()) {
                switch (player->get_powerup_type()) {
                    case EntityType::Mushroom:
                        player->set_is_damaged(true);
                        player->set_has_powerup(false);
                        break;
                    case EntityType::Star:
                        enemy.set_is_dead(true);
                        game_renderer->clear_point(enemy.get_position());
                        break;
                }
            } else {
                player->set_is_damaged(true);
                player->remove_health(ENEMY_DAMAGE);
                player->jump();
            }
        }
    }
}

void GameManager::game_over_screen() {
    game_renderer->render_2d_char_array(ascii_texts.get_game_over(), Alignment::Center, Alignment::Center);
}

void GameManager::main_loop() {
    bool should_continue = true;

    try {
        while (should_continue) {
            input_manager.read_input(game_renderer->get_win());

            if (game_timer.should_tick()) {
                player->tick();
                level->tick(player->get_position());
                game_renderer->render_all();

                handle_enemy_collisions();

                if (player->get_health() <= 0) {
                    // game over and wait for ' ' to restart
                    game_over_screen();
                    input_manager.wait_for_btn(game_renderer->get_win(), ' ');
                    game_renderer->clear_screen();

                    // restart game (reset player health and position, current room back to first room)
                    level->restart_from_first_room();
                    player->set_health(PLAYER_STARTING_HEALTH);
                    player->set_position(level->get_cur_room()->get_player_start_position());
                }

                if (level->should_change_room()) {
                    level->execute_room_change();

                    Room* cur_room = level->get_cur_room();
                    player->refresh(cur_room->get_player_start_position(), &cur_room->get_floor(), &cur_room->get_ceiling(), &cur_room->get_platforms(), &cur_room->get_powerups());

                    game_renderer->clear_screen();
                }

                should_continue = !input_manager.is_key_pressed(QUIT_KEY);
                input_manager.clear_input_buff();
            }
        }
    } catch (const std::exception& e) {
        cleanup();
        std::cerr << e.what() << std::endl;
        exit(EXIT_FAILURE);
    }
}

void GameManager::begin() {
    std::srand(std::time(nullptr));

    splash_screen();  // wait for ' ' to start
    level->load_first_room();

    main_loop();
}

void GameManager::cleanup() {
    game_renderer->cleanup();
    level->cleanup();

    delete level;
    delete player;
    delete game_renderer;

    for (int i = 0; i < rooms.length(); i++) {
        delete rooms.at(i);
    }

    for (int i = 0; i < powerups.length(); i++) {
        delete powerups.at(i);
    }
}
