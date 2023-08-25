#include "gamemanager.hpp"

GameManager::GameManager()
    : game_timer(TICK_INTERVAL),
      input_manager(),
      game_maps(),
      ascii_texts() {
    rooms = List<Room>();
    rooms.push(game_maps.layout1());
    rooms.push(game_maps.layout2());
    rooms.push(game_maps.layout3());

    powerups = List<Powerup*>();

    level = new LevelManager(&rooms, game_timer);

    player = new Player(game_timer, input_manager, level->get_cur_room()->get_player_start_position(), level->get_cur_room()->get_floor(), level->get_cur_room()->get_ceiling(), level->get_cur_room()->get_platforms(), powerups);

    game_renderer = new GameRenderer(player, level, &game_timer);

    game_timer.start();
    game_renderer->initialize();
}

void GameManager::splash_screen() {
    game_renderer->render_2d_char_array(ascii_texts.get_splash(), Alignment::Center, Alignment::Center);

    input_manager.wait_for_btn(game_renderer->get_win(), ' ');
    game_renderer->clear_screen();
}

void GameManager::tick_all() {
    player->tick();
    level->tick(player->get_position());
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

    while (should_continue) {
        input_manager.read_input(game_renderer->get_win());

        if (game_timer.should_tick()) {
            tick_all();
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
                game_renderer->clear_screen();
                player->set_position(level->get_cur_room()->get_player_start_position());
            }

            should_continue = !input_manager.is_key_pressed(QUIT_KEY);
            input_manager.clear_input_buff();
        }
    }
}

void GameManager::begin() {
    splash_screen();  // wait for ' ' to start
    level->load_first_room();

    main_loop();
}
