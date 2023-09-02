#include "gamemanager.hpp"

GameManager::GameManager()
    : game_timer(TICK_INTERVAL),
      input_manager(),
      game_maps(),
      ascii_texts() {
    std::srand((unsigned)std::time(nullptr));

    rooms = *game_maps.get_all_rooms();
    // Layouts Debug ONLY!!
    // rooms = List<Room*>();
    // rooms.push(game_maps.get_room(0));
    // rooms.push(game_maps.get_room(1));

    powerups = List<Powerup*>();
    level = new LevelManager(&rooms);
    level->initialize(STARTING_DIFFICULTY);
    player = new Player(&input_manager, level->get_cur_room()->get_player_start_position(), &level->get_cur_room()->get_floor(), &level->get_cur_room()->get_ceiling(), &level->get_cur_room()->get_platforms(), &powerups);
    shop = new Shop(player, &input_manager);
    game_renderer = new GameRenderer(player, level, &game_timer);

    game_timer.start();
    game_renderer->initialize();
}

void GameManager::splash_screen() {
    game_renderer->render_2d_char_array(ascii_texts.get_splash(), Alignment::Center, Alignment::Center);

    input_manager.wait_for_btn(game_renderer->get_win(), ' ');
    game_renderer->clear_screen();
}

void GameManager::handle_collisions() {
    // enemies - player
    for (int i = 0; i < level->get_cur_room()->get_enemies().length(); i++) {
        Enemy& enemy = level->get_cur_room()->get_enemies().at(i);

        if (collides(player, &enemy) && !enemy.get_is_dead()) {
            if (player->get_has_powerup()) {
                switch (player->get_powerup_type()) {
                    case EntityType::Mushroom:
                    case EntityType::Gun:
                        // player->set_is_damaged(true);
                        player->jump();
                        player->remove_powerup();
                        break;
                    case EntityType::Star:
                        enemy.set_is_dead(true);
                        game_renderer->clear_point(enemy.get_position());
                        break;
                    default:
                        break;
                }
            } else {
                player->set_is_damaged(true);
                player->remove_health(ENEMY_DAMAGE);
                player->jump();
            }
        }
    }

    // projectiles - player, enemies
    for (int i = 0; i < level->get_cur_room()->get_projectiles().length(); i++) {
        Projectile* projectile = level->get_cur_room()->get_projectiles().at(i);

        if (projectile->is_out_of_bounds()) {
            game_renderer->clear_point(projectile->get_position());
            level->get_cur_room()->remove_projectile(projectile);
            continue;
        }

        // with player
        if (projectile->get_shot_by() != EntityType::Player && collides(projectile, player)) {
            if (player->get_has_powerup()) {
                switch (player->get_powerup_type()) {
                    case EntityType::Mushroom:
                    case EntityType::Gun:
                        // player->set_is_damaged(true);
                        player->jump();
                        player->remove_powerup();
                        break;
                    default:
                        break;
                }
            } else {
                player->set_is_damaged(true);
                player->remove_health(PROJECTILE_DAMAGE);
                player->jump();
            }
            // remove projectile
            game_renderer->clear_point(projectile->get_position());
            level->get_cur_room()->remove_projectile(projectile);
        }

        // with enemies
        bool should_continue = true;
        for (int j = 0; should_continue && j < level->get_cur_room()->get_enemies().length(); j++) {
            Enemy& enemy = level->get_cur_room()->get_enemies().at(j);

            if (projectile->get_shot_by() != EntityType::Enemy && collides(projectile, &enemy) && !enemy.get_is_dead()) {
                enemy.set_is_dead(true);
                game_renderer->clear_point(enemy.get_position());
                game_renderer->clear_point(projectile->get_position());
                game_renderer->clear_point(projectile->get_position());
                level->get_cur_room()->remove_projectile(projectile);
                should_continue = false;
            }
        }
    }
}

void GameManager::handle_player_shooting() {
    if (player->should_shoot()) {
        Room* cur_room = level->get_cur_room();
        Position projectile_position = (Position){.x = player->get_position().x + (player->get_direction() == Direction::Left ? -1 : 1), .y = player->get_position().y};
        Projectile* projectile = new Projectile(projectile_position, &cur_room->get_floor(), &cur_room->get_ceiling(), &cur_room->get_platforms(), EntityType::Player);
        level->get_cur_room()->add_projectile(projectile);
        projectile->start(player->get_direction());
        player->reset_shoot();
    }
}

void GameManager::handle_enemies_shooting() {
    Room* cur_room = level->get_cur_room();

    for (int i = 0; i < cur_room->get_enemies().length(); i++) {
        Enemy& enemy = cur_room->get_enemies().at(i);

        if (!enemy.get_is_dead() && enemy.should_shoot() && level->get_cur_difficulty() >= ENEMY_SHOOTING_MIN_DIFFICULTY) {
            Projectile* projectile = new Projectile(enemy.get_position(), &cur_room->get_floor(), &cur_room->get_ceiling(), &cur_room->get_platforms(), EntityType::Enemy);
            cur_room->add_projectile(projectile);
            projectile->start(enemy.get_direction());
            enemy.reset_shoot();
        }
    }
}

void GameManager::refresh_player() {
    Room* cur_room = level->get_cur_room();
    player->refresh(cur_room->get_player_start_position(), &cur_room->get_floor(), &cur_room->get_ceiling(), &cur_room->get_platforms(), &cur_room->get_powerups());
}

void GameManager::game_over_screen() {
    game_renderer->render_2d_char_array(ascii_texts.get_game_over(), Alignment::Center, Alignment::Center);
}

void GameManager::shop_loop() {
    input_manager.clear_input_buff();

    bool should_continue = true;

    List<int>* shop_controls = shop->get_shop_controls();

    // altrimenti timer stella continua ad andare mentre si e' nello shop
    bool player_has_star = player->has_star();

    while (should_continue) {
        game_renderer->render_shop(ascii_texts.get_shop(), shop->get_buyable_powerups_ptr(), shop->get_cur_index_ptr(), player->get_coins(), player->get_powerup_type(), level->get_total_visited_room_count(), shop->get_should_show_no_coins_message(), shop->get_should_show_powerup_bought_message());
        int key = input_manager.wait_for_btns(game_renderer->get_win(), *shop_controls);
        shop->handle_key_press(key);

        should_continue = key != (int)ShopControls::Quit;
        input_manager.clear_input_buff();
    }

    if (shop->get_should_apply_star() || player_has_star)
        player->add_star();
    shop->reset_shop_status();
    game_renderer->clear_screen();
}

void GameManager::main_loop() {
    shop_loop();

    bool should_continue = true;

    try {
        while (should_continue) {
            input_manager.read_input(game_renderer->get_win());

            if (game_timer.should_tick()) {
                player->tick();
                level->tick(player->get_position());
                game_renderer->render_game();

                handle_player_shooting();
                handle_collisions();
                handle_enemies_shooting();

                if (player->get_health() <= 0) {
                    // game over and wait for ' ' to restart
                    game_over_screen();
                    game_renderer->render_high_score(level->get_total_visited_room_count(), level->get_cur_difficulty());

                    input_manager.wait_for_btn(game_renderer->get_win(), ' ');
                    game_renderer->clear_screen();

                    int last_difficulty = level->get_cur_difficulty();

                    // restart game (reset player health and position, current room back to first room)
                    level->initialize(last_difficulty);
                    level->load_first_room();
                    refresh_player();
                    player->set_health(PLAYER_STARTING_HEALTH);
                    player->set_position(level->get_cur_room()->get_player_start_position());

                    shop_loop();
                } else if (level->should_change_room()) {
                    level->execute_room_change();
                    refresh_player();
                    game_renderer->clear_screen();

                    if (level->get_cur_visited_room_index() % 3 == 0)
                        shop_loop();
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
    splash_screen();  // wait for ' ' to start
    level->load_first_room();
    refresh_player();

    main_loop();
}

void GameManager::cleanup() {
    game_renderer->cleanup();
    level->cleanup();

    delete level;
    delete player;
    delete game_renderer;
    delete shop;

    for (int i = 0; i < rooms.length(); i++) {
        delete rooms.at(i);
    }

    for (int i = 0; i < powerups.length(); i++) {
        delete powerups.at(i);
    }
}
