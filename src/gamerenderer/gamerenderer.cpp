#include "gamerenderer.hpp"

#include "../coin/coin.hpp"

#include <cstring>
#include <iostream>

#define TEXT_WHITE 1
#define BG_WHITE 2
#define BG_BLUE 3
#define BG_MAGENTA 4
#define BG_YELLOW 5
#define TEXT_RED 6
#define TEXT_YELLOW 7
#define TEXT_BLUE 8
#define TEXT_GREEN 9

GameRenderer::GameRenderer(Player* player, LevelManager* level_manager, GameTimer* timer)
    : player(player),
      level_manager(level_manager),
      game_timer(timer) {}

void GameRenderer::cleanup() {
    delwin(win);
    endwin();
}

void GameRenderer::initialize() {
    int width, height;
    initscr();                                          // Inizializza la finestra ncurses
    start_color();                                      // Abilita il sistema di colori
    init_pair(TEXT_WHITE, COLOR_WHITE, COLOR_BLACK);    // Testo bianco su sfondo nero (id, foreground, background)
    init_pair(BG_WHITE, COLOR_BLACK, COLOR_WHITE);      //
    init_pair(BG_BLUE, COLOR_BLACK, COLOR_BLUE);        //
    init_pair(BG_MAGENTA, COLOR_BLACK, COLOR_MAGENTA);  //
    init_pair(BG_YELLOW, COLOR_BLACK, COLOR_YELLOW);    //
    init_pair(TEXT_RED, COLOR_RED, COLOR_BLACK);        //
    init_pair(TEXT_YELLOW, COLOR_YELLOW, COLOR_BLACK);  //
    init_pair(TEXT_BLUE, COLOR_BLUE, COLOR_BLACK);      //
    init_pair(TEXT_GREEN, COLOR_GREEN, COLOR_BLACK);    //
    timeout(-1);                                        // Disabilita timeout di getch
    cbreak();                                           // Disabilita il buffering del tasto Invio
    raw();                                              // Disabilita il buffer di input line-by-line
    keypad(stdscr, TRUE);                               // Abilita la lettura dei tasti speciali
    noecho();                                           // Non mostrare l'input utente
    curs_set(0);                                        // Nascondi il cursore
    getmaxyx(stdscr, height, width);                    // Imposta larghezza e altezza
    // check_terminal_size(width, height);

    // Crea la finestra principale
    win = newwin(GAME_HEIGHT, GAME_WIDTH, 0, 0);
    keypad(win, TRUE);
    wbkgd(win, COLOR_PAIR(1));

    render_border();
}

void GameRenderer::check_terminal_size(int width, int height) {
    if (width < GAME_WIDTH || height < GAME_HEIGHT) {
        throw std::runtime_error("Terminal must be at least " +
                                 std::to_string(GAME_WIDTH) + "x" +
                                 std::to_string(GAME_HEIGHT) +
                                 " current size: " + std::to_string(width) +
                                 "x" + std::to_string(height));
    }
}

void GameRenderer::render_border() {
    // Stampa il bordo superiore
    mvwhline(win, 0, 1, ACS_HLINE, GAME_WIDTH - 2);

    // Stampa il bordo sinistro e destro
    mvwvline(win, 1, 0, ACS_VLINE, GAME_HEIGHT - 2);
    mvwvline(win, 1, GAME_WIDTH - 1, ACS_VLINE, GAME_HEIGHT - 2);

    // Stampa il bordo inferiore
    mvwhline(win, GAME_HEIGHT - 1, 1, ACS_HLINE, GAME_WIDTH - 2);

    // Stampa gli angoli del bordo
    mvwaddch(win, 0, 0, ACS_ULCORNER);
    mvwaddch(win, 0, GAME_WIDTH - 1, ACS_URCORNER);
    mvwaddch(win, GAME_HEIGHT - 1, 0, ACS_LLCORNER);
    mvwaddch(win, GAME_HEIGHT - 1, GAME_WIDTH - 1, ACS_LRCORNER);
}

void GameRenderer::render_player_character(Position position) {
    bool player_has_mushroom = player->get_has_powerup() && player->get_powerup_type() == EntityType::Mushroom;
    bool player_has_gun = player->get_has_powerup() && player->get_powerup_type() == EntityType::Gun;
    bool player_has_star = player->has_star() && player->should_show_star();

    if (player->get_is_damaged() && player->damaged_should_tick()) {
        wattron(win, COLOR_PAIR(TEXT_RED));
        render_str(position, player_has_mushroom ? PLAYER_POWERUP_RENDER_CHARACTER : PLAYER_RENDER_CHARACTER);
        wattroff(win, COLOR_PAIR(TEXT_RED));
    } else if (player_has_mushroom) {
        wattron(win, COLOR_PAIR(TEXT_YELLOW));
        render_str(position, PLAYER_POWERUP_RENDER_CHARACTER);
        wattroff(win, COLOR_PAIR(TEXT_YELLOW));
    } else if (player_has_gun) {
        wattron(win, COLOR_PAIR(TEXT_YELLOW));
        render_str(position, PLAYER_GUN_RENDER_CHARACTER);
        wattroff(win, COLOR_PAIR(TEXT_YELLOW));
    } else if (player_has_star) {
        wattron(win, COLOR_PAIR(TEXT_YELLOW));
        render_str(position, PLAYER_RENDER_CHARACTER);
        wattroff(win, COLOR_PAIR(TEXT_YELLOW));
    } else {
        render_str(position, PLAYER_RENDER_CHARACTER);
    }
}

void GameRenderer::render_player() {
    Position player_pos = player->get_position();
    Position last_player_pos = player->get_last_position();

    // cancello vecchio player
    render_str(last_player_pos, " ");
    render_player_character(player_pos);
}

void GameRenderer::render_enemies() {
    for (int i = 0; i < level_manager->get_cur_room()->get_enemies().length(); i++) {
        Enemy enemy = level_manager->get_cur_room()->get_enemies().at(i);
        if (enemy.get_is_dead())
            continue;

        Position enemy_pos = enemy.get_position();
        Position last_enemy_pos = enemy.get_last_position();

        // cancello vecchio enemy
        render_str(last_enemy_pos, " ");
        render_str(enemy_pos, ENEMY_RENDER_CHARACTER);
    }
}

void GameRenderer::render_powerups() {
    for (int i = 0; i < level_manager->get_cur_room()->get_powerups().length(); i++) {
        Powerup* powerup = level_manager->get_cur_room()->get_powerups().at(i);
        if (powerup == nullptr)
            throw std::runtime_error("Null pointer exception at GameRenderer::render_powerups()");

        Position powerup_pos = powerup->get_position();

        if (powerup->get_entity_type() == EntityType::Coin) {
            // cast to Coin
            Coin* coin = (Coin*)powerup;
            wattron(win, COLOR_PAIR(TEXT_YELLOW));
            rectangle(powerup_pos, (Position){.x = powerup->get_ur().x + coin->get_digits() - 1, .y = powerup->get_ur().y});
            wattroff(win, COLOR_PAIR(TEXT_YELLOW));
        } else {
            wattron(win, COLOR_PAIR(TEXT_BLUE));
            rectangle(powerup_pos, powerup->get_ur());
            wattroff(win, COLOR_PAIR(TEXT_BLUE));
        }

        Position char_pos = (Position){.x = powerup_pos.x + 2, .y = powerup_pos.y - 1};

        bool is_active = powerup->get_is_active();
        wattron(win, COLOR_PAIR(is_active ? TEXT_YELLOW : TEXT_BLUE));
        render_str(char_pos, powerup->get_is_active() ? powerup->get_render_char() : POWERUP_RENDER_DISABLED_CHARACTER);
        if (!powerup->get_is_active() && powerup->get_entity_type() == EntityType::Coin && ((Coin*)powerup)->get_digits() > 1)
            render_str((Position){.x = char_pos.x + 1, .y = char_pos.y}, POWERUP_RENDER_DISABLED_CHARACTER);
        wattroff(win, COLOR_PAIR(is_active ? TEXT_YELLOW : TEXT_BLUE));
    }
}

void GameRenderer::render_projectiles() {
    for (int i = 0; i < level_manager->get_cur_room()->get_projectiles().length(); i++) {
        Projectile* projectile = level_manager->get_cur_room()->get_projectiles().at(i);

        Position projectile_pos = projectile->get_position();
        Position last_projectile_pos = projectile->get_last_position();

        // cancello vecchio projectile
        render_str(last_projectile_pos, " ");
        render_str(projectile_pos, PROJECTILE_RENDER_CHARACTER);
    }
}

void GameRenderer::rectangle(Position _pos1, Position _pos2) {
    Position pos1 = translate_position(_pos1);
    Position pos2 = translate_position(_pos2);

    mvwhline(win, pos1.y, pos1.x, 0, pos2.x - pos1.x);
    mvwhline(win, pos2.y, pos1.x, 0, pos2.x - pos1.x);
    mvwvline(win, pos1.y, pos1.x, 0, pos2.y - pos1.y);
    mvwvline(win, pos1.y, pos2.x, 0, pos2.y - pos1.y);
    mvwaddch(win, pos1.y, pos1.x, ACS_ULCORNER);
    mvwaddch(win, pos2.y, pos1.x, ACS_LLCORNER);
    mvwaddch(win, pos1.y, pos2.x, ACS_URCORNER);
    mvwaddch(win, pos2.y, pos2.x, ACS_LRCORNER);
}

void GameRenderer::empty_rectangle(Position pos1, Position pos2) {
    for (int y = 0; y < pos2.y - pos1.y; y++) {
        for (int x = 0; x < pos2.x - pos1.x; x++) {
            render_str((Position){.x = pos1.x + x, .y = pos1.y + y}, " ");
        }
    }
}

void GameRenderer::render_platforms() {
    for (int i = 0; i < level_manager->get_cur_room()->get_platforms().length(); i++) {
        Platform platform = level_manager->get_cur_room()->get_platforms().at(i);

        Position pos1 = platform.get_position();
        Position pos2 = platform.get_ur();
        std::swap(pos1.y, pos2.y);

        rectangle(pos1, pos2);
    }
}

void GameRenderer::render_start_end_regions() {
    // render start region

    // DEBUG uncomment
    if (level_manager->get_visited_rooms_count() > 1) {
        wattron(win, COLOR_PAIR(BG_BLUE));
        empty_rectangle(
            level_manager->get_cur_room()->get_start_region().get_position(),
            level_manager->get_cur_room()->get_start_region().get_ur());
        wattroff(win, COLOR_PAIR(BG_BLUE));
    }

    // render end region
    wattron(win, COLOR_PAIR(BG_MAGENTA));
    empty_rectangle(
        level_manager->get_cur_room()->get_end_region().get_position(),
        level_manager->get_cur_room()->get_end_region().get_ur());
    wattroff(win, COLOR_PAIR(BG_MAGENTA));
}

void GameRenderer::clear_point(Position position) {
    render_str(position, " ");
}

void GameRenderer::clear_screen() {
    wclear(win);
}

WINDOW* GameRenderer::get_win() const {
    return win;
}

void GameRenderer::refresh_screen() {
    wrefresh(win);
}

void GameRenderer::render_shop_items(List<Buyable>* items, int* currently_selected_index, int coins) {
    int total_boxes_width = items->length() * SHOP_BOX_WIDTH;

    for (int i = 0; i < items->length(); i++) {
        Buyable item = items->at(i);
        Position item_pos = (Position){.x = (GAME_WIDTH - total_boxes_width) / 2 + i * SHOP_BOX_WIDTH * 4 / 3, .y = 15};

        int w_half = SHOP_BOX_WIDTH / 2;

        wattron(win, COLOR_PAIR(i == (*currently_selected_index) ? TEXT_YELLOW : TEXT_BLUE));
        rectangle((Position){.x = item_pos.x - w_half, .y = item_pos.y + 2}, (Position){.x = item_pos.x + w_half, .y = item_pos.y - 2});
        wattroff(win, COLOR_PAIR(i == (*currently_selected_index) ? TEXT_YELLOW : TEXT_BLUE));

        char str_to_render[STR_BUF];
        sprintf(str_to_render, "%c %s", item.symbol, item.name);

        render_str((Position){.x = item_pos.x - (int)strlen(str_to_render) / 2, .y = item_pos.y}, str_to_render);

        render_str_num((Position){.x = item_pos.x - (int)strlen(str_to_render) / 2 + 1, .y = item_pos.y - 2}, " ", item.price);
        // item.price
    }
}

void GameRenderer::render_shop_top_bar(List<Buyable>* items, EntityType player_powerup) {
    render_str((Position){.x = GAME_WIDTH / 3, .y = 20}, "Powerup attuale:");

    wattron(win, COLOR_PAIR(TEXT_YELLOW));

    bool found = false;
    for (int i = 0; i < items->length(); i++) {
        if (items->at(i).type == player_powerup) {
            render_str((Position){.x = GAME_WIDTH / 3 + 18, .y = 20}, items->at(i).name);
            found = true;
            break;
        }
    }
    if (!found) {
        render_str((Position){.x = GAME_WIDTH / 3 + 18, .y = 20}, "Nessuno");
    }

    wattroff(win, COLOR_PAIR(TEXT_YELLOW));

    render_player_character((Position){.x = 2 * GAME_WIDTH / 3, .y = 20});

    wattron(win, COLOR_PAIR(TEXT_YELLOW));
    rectangle((Position){.x = 2 * GAME_WIDTH / 3 - 2, .y = 21}, (Position){.x = 2 * GAME_WIDTH / 3 + 2, .y = 19});
    wattroff(win, COLOR_PAIR(TEXT_YELLOW));
}

void GameRenderer::render_shop_bottom_bar(int cur_rooms_completed, bool show_no_coins, bool show_bought) {
    render_str((Position){.x = GAME_WIDTH / 3 - 17, .y = 7}, "Stanze completate");
    render_str_num((Position){.x = GAME_WIDTH / 3 - 10, .y = 6}, "", cur_rooms_completed - 1);

    render_str((Position){.x = GAME_WIDTH / 2, .y = 8}, "W");
    render_str((Position){.x = GAME_WIDTH / 2 - 5, .y = 5}, "A");
    render_str((Position){.x = GAME_WIDTH / 2, .y = 5}, "S");
    render_str((Position){.x = GAME_WIDTH / 2 + 5, .y = 5}, "D");
    rectangle((Position){.x = GAME_WIDTH / 2 - 2, .y = 9}, (Position){.x = GAME_WIDTH / 2 + 2, .y = 7});
    rectangle((Position){.x = GAME_WIDTH / 2 - 7, .y = 6}, (Position){.x = GAME_WIDTH / 2 - 3, .y = 4});
    rectangle((Position){.x = GAME_WIDTH / 2 - 2, .y = 6}, (Position){.x = GAME_WIDTH / 2 + 2, .y = 4});
    rectangle((Position){.x = GAME_WIDTH / 2 + 3, .y = 6}, (Position){.x = GAME_WIDTH / 2 + 7, .y = 4});

    render_str((Position){.x = 2 * GAME_WIDTH / 3, .y = 8}, "Compra");
    render_str((Position){.x = 2 * GAME_WIDTH / 3 + 9, .y = 8}, "Spazio");
    rectangle((Position){.x = 2 * GAME_WIDTH / 3 + 7, .y = 9}, (Position){.x = 2 * GAME_WIDTH / 3 + 16, .y = 7});
    render_str((Position){.x = 2 * GAME_WIDTH / 3, .y = 5}, "Esci dallo shop");
    render_str((Position){.x = 2 * GAME_WIDTH / 3 + 19, .y = 5}, "Q");
    rectangle((Position){.x = 2 * GAME_WIDTH / 3 + 17, .y = 6}, (Position){.x = 2 * GAME_WIDTH / 3 + 21, .y = 4});

    if (show_no_coins) {
        wattron(win, COLOR_PAIR(BG_YELLOW));
        const char* msg = " Non hai abbastanza monete! ";
        render_str((Position){.x = GAME_WIDTH / 2 - (int)strlen(msg) / 2, .y = 11}, msg);
        wattroff(win, COLOR_PAIR(BG_YELLOW));
    } else if (show_bought) {
        wattron(win, COLOR_PAIR(BG_YELLOW));
        const char* msg = " Hai comprato il powerup! ";
        render_str((Position){.x = GAME_WIDTH / 2 - (int)strlen(msg) / 2, .y = 11}, msg);
        wattroff(win, COLOR_PAIR(BG_YELLOW));
    }
}

void GameRenderer::pretty_print_coins(Position position, int amount) {
    int coins_digits = std::to_string(amount).length();

    render_str_num((Position){.x = position.x + COINS_RENDER_DIGITS - coins_digits, .y = position.y}, "", amount);
    for (int i = 0; i < COINS_RENDER_DIGITS - coins_digits; i++) {
        // manuale senno' stampa il padding che nasconde le cifre
        wattron(win, COLOR_PAIR(TEXT_YELLOW));
        mvwprintw(win, translate_y(position.y), position.x + i + 1, "%s", "0");
        wattroff(win, COLOR_PAIR(TEXT_YELLOW));
    }
    wattroff(win, COLOR_PAIR(TEXT_YELLOW));
}

int GameRenderer::translate_y(int y) const {
    return GAME_HEIGHT - y;
};

Position GameRenderer::translate_position(Position position) const {
    return (Position){.x = position.x, .y = GAME_HEIGHT - position.y};
};

void GameRenderer::render_str(Position _position, const char* str) const {
    Position position = translate_position(_position);
    mvwprintw(win, position.y, position.x, "%s", str);
};

void GameRenderer::render_str_num(Position position, const char* str, int number) const {
    render_str(position, str);
    wattron(win, COLOR_PAIR(TEXT_YELLOW));
    wprintw(win, " %d  ", number);
    wattroff(win, COLOR_PAIR(TEXT_YELLOW));
}

void GameRenderer::render_game() {
    // render_debug_status();
    render_top_bar();
    render_powerups();
    render_start_end_regions();
    render_projectiles();
    render_player();
    render_enemies();
    render_floor();
    render_platforms();
    render_border();
    refresh_screen();
}

void GameRenderer::render_shop(List<const char*> title, List<Buyable>* items, int* currently_selected_index, int coins, EntityType player_powerup, int cur_rooms_completed, bool show_no_coins, bool show_bought) {
    render_2d_char_array(title, Alignment::End, Alignment::Beginning);  // title
    render_top_bar();
    render_border();
    render_shop_items(items, currently_selected_index, coins);
    render_shop_top_bar(items, player_powerup);
    render_shop_bottom_bar(cur_rooms_completed, show_no_coins, show_bought);
    refresh_screen();
}

void GameRenderer::render_2d_char_array(List<const char*> text, Alignment h_align, Alignment v_align) {
    clear_screen();

    int height = text.length();

    int y = height - 1;

    int text_length = (int)(strlen(text.at(0)));

    while (y >= 0) {
        int x = RENDER_TEXT_X_PADDING;
        if (h_align == Alignment::Center) {
            x = (GAME_WIDTH - text_length) / 2;
        } else if (h_align == Alignment::End) {
            x = GAME_WIDTH - text_length - RENDER_TEXT_X_PADDING;
        }

        int y_pos = RENDER_TEXT_Y_PADDING;
        if (v_align == Alignment::Center) {
            y_pos = (GAME_HEIGHT - height) / 2;
        } else if (v_align == Alignment::Beginning) {
            y_pos = GAME_HEIGHT - height - RENDER_TEXT_Y_PADDING;
        }

        render_str((Position){.x = x, .y = y_pos + height - y}, text.at(y));
        y--;

        // std::cout << correct_pos.x << " - " << correct_pos.y << std::endl;
    }

    render_border();
    refresh_screen();
}

void GameRenderer::render_floor() {
    wattron(win, COLOR_PAIR(TEXT_GREEN));

    Position prev_native_pos = translate_position((Position){.x = 0, .y = level_manager->get_cur_room()->get_floor_at(0)});

    for (int i = 0; i < level_manager->get_cur_room()->get_width(); i++) {
        int cur_height = level_manager->get_cur_room()->get_floor_at(i);
        int native_height = translate_y(cur_height);

        if (native_height == prev_native_pos.y && i != GAME_WIDTH - 1)
            continue;

        // forse solo i - 1, documentazione di merda
        mvwhline(win, prev_native_pos.y, prev_native_pos.x + 1, ACS_HLINE,
                 i - prev_native_pos.x - 1);

        // caso in cui non sei all'ultimo render ma c'e' differenza di altezza:
        // congiungi
        if (native_height != prev_native_pos.y) {
            auto m = std::min(prev_native_pos.y, native_height);
            auto M = std::max(prev_native_pos.y, native_height);
            mvwvline(win, m + 1, i, ACS_VLINE, M - m - 1);

            // angoli
            if (prev_native_pos.y < native_height) {
                mvwaddch(win, prev_native_pos.y, i, ACS_URCORNER);
                mvwaddch(win, native_height, i, ACS_LLCORNER);
            } else {
                mvwaddch(win, prev_native_pos.y, i, ACS_LRCORNER);
                mvwaddch(win, native_height, i, ACS_ULCORNER);
            }
        }

        // render_str((Position){.x = i, .y = cur_height}, std::to_string(cur_height).c_str());

        prev_native_pos = (Position){.x = i, .y = native_height};
    }

    wattroff(win, COLOR_PAIR(TEXT_GREEN));
}

void GameRenderer::render_top_bar() {
    // salute
    render_str((Position){.x = 6, .y = GAME_HEIGHT - 2}, PLAYER_NAME);

    wattron(win, COLOR_PAIR(TEXT_RED));

    int health = player->get_health();
    int full_hearts = health / 10;
    int empty_hearts = (PLAYER_MAX_HEALTH - health) / 10;

    for (int i = 0; i < full_hearts; i++) {
        render_str((Position){.x = 5 + i, .y = GAME_HEIGHT - 3}, "o");
    }

    wattroff(win, COLOR_PAIR(TEXT_RED));

    for (int i = 0; i < empty_hearts; i++) {
        render_str((Position){.x = 5 + (full_hearts + i), .y = GAME_HEIGHT - 3}, "o");
    }

    // monete
    render_str((Position){.x = 30, .y = GAME_HEIGHT - 2}, "Monete");
    wattron(win, COLOR_PAIR(TEXT_YELLOW));
    // stampa leading zeros = 3 - numero di cifre
    pretty_print_coins((Position){.x = 31, .y = GAME_HEIGHT - 3}, player->get_coins());

    // difficolta
    render_str((Position){.x = 50, .y = GAME_HEIGHT - 2}, "Difficolta'");
    wattron(win, COLOR_PAIR(TEXT_YELLOW));
    render_str_num((Position){.x = 54, .y = GAME_HEIGHT - 3}, "", level_manager->get_cur_difficulty());
    wattroff(win, COLOR_PAIR(TEXT_YELLOW));

    // TODO remove debug
    // debug: print player coordinates
    // render_str_num((Position){.x = 70, .y = GAME_HEIGHT - 2}, "x", (int)player->get_position().x);
    // render_str_num((Position){.x = 70, .y = GAME_HEIGHT - 3}, "y", (int)player->get_position().y);

    // debug: print health num
    // render_str_num((Position){.x = 68, .y = GAME_HEIGHT - 5}, "health", (int)player->get_health());

    // print start end regions
    // render_str_num((Position){.x = 78, .y = GAME_HEIGHT - 2}, "start_x from", (int)level_manager->get_cur_room()->get_start_region().get_position().x);
    // render_str_num((Position){.x = 78, .y = GAME_HEIGHT - 3}, "start_y from", (int)level_manager->get_cur_room()->get_start_region().get_position().y);
    // render_str_num((Position){.x = 78, .y = GAME_HEIGHT - 4}, "start_x to", (int)level_manager->get_cur_room()->get_start_region().get_ur().x);
    // render_str_num((Position){.x = 78, .y = GAME_HEIGHT - 5}, "start_y to", (int)level_manager->get_cur_room()->get_start_region().get_ur().y);
    // render_str_num((Position){.x = 94, .y = GAME_HEIGHT - 2}, "end_x from", (int)level_manager->get_cur_room()->get_end_region().get_position().x);
    // render_str_num((Position){.x = 94, .y = GAME_HEIGHT - 3}, "end_y from", (int)level_manager->get_cur_room()->get_end_region().get_position().y);
    // render_str_num((Position){.x = 94, .y = GAME_HEIGHT - 4}, "end_x to", (int)level_manager->get_cur_room()->get_end_region().get_ur().x);
    // render_str_num((Position){.x = 94, .y = GAME_HEIGHT - 5}, "end_y to", (int)level_manager->get_cur_room()->get_end_region().get_ur().y);
}

void GameRenderer::render_debug_status() {
    // render_str_num((Position){.x = 2, .y = GAME_HEIGHT - 1}, "last_tick", (int)(game_timer->last_tick_time.time_since_epoch() / std::chrono::milliseconds(1)));

    render_str_num((Position){.x = 2, .y = GAME_HEIGHT - 6}, "is_on_floor", (int)player->is_on_floor());
    render_str_num((Position){.x = 2, .y = GAME_HEIGHT - 7}, "is_touching_ceiling", (int)player->is_touching_ceiling());
    render_str_num((Position){.x = 2, .y = GAME_HEIGHT - 8}, "has_wall_on_left", (int)player->has_wall_on_left());
    render_str_num((Position){.x = 2, .y = GAME_HEIGHT - 9}, "has_wall_on_right", (int)player->has_wall_on_right());
    render_str_num((Position){.x = 2, .y = GAME_HEIGHT - 10}, "is_jumping", (int)player->is_jumping);

    render_str_num((Position){.x = 2, .y = GAME_HEIGHT - 12}, "vel_x", (int)player->vel_x);
    render_str_num((Position){.x = 2, .y = GAME_HEIGHT - 13}, "vel_y", (int)player->vel_y);

    render_str_num((Position){.x = 2, .y = GAME_HEIGHT - 15}, "x", (int)player->get_position().x);
    render_str_num((Position){.x = 2, .y = GAME_HEIGHT - 16}, "y", (int)player->get_position().y);

    render_str_num((Position){.x = 2, .y = GAME_HEIGHT - 18}, "floor[x]", (int)level_manager->get_cur_room()->get_floor_at(player->get_position().x));
    render_str_num((Position){.x = 2, .y = GAME_HEIGHT - 19}, "ceiling[x]", (int)level_manager->get_cur_room()->get_ceiling_at(player->get_position().x));

    render_str_num((Position){.x = 2, .y = GAME_HEIGHT - 21}, "health", (int)player->get_health());
    render_str_num((Position){.x = 2, .y = GAME_HEIGHT - 22}, "on_platform", (int)player->is_on_platform());
}