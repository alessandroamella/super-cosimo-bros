#include "gamerenderer.hpp"

#include <cstring>
#include <iostream>

GameRenderer::GameRenderer(Player& player, LevelManager& cur_level,
                           GameTimer& timer, InputManager& input_manager)
    : player(player),
      cur_level(cur_level),
      game_timer(timer),
      input_manager(input_manager) {}

GameRenderer::~GameRenderer() {
    endwin();  // Chiudi la finestra ncurses alla distruzione dell'oggetto
}

void GameRenderer::initialize() {
    int width, height;
    initscr();             // Inizializza la finestra ncurses
    timeout(-1);           // Disabilita timeout di getch
    cbreak();              // Disabilita il buffering del tasto Invio
    raw();                 // Disabilita il buffer di input line-by-line
    keypad(stdscr, TRUE);  // Abilita la lettura dei tasti speciali
    noecho();              // Non mostrare l'input utente
    curs_set(0);           // Nascondi il cursore
    getmaxyx(stdscr, height, width);  // Imposta larghezza e altezza
    check_terminal_size(width, height);
    render_border();

    // Nota: nodelay non viene chiamato dunque all'inizio getch è bloccante!!
    // Bisogna chiamare wait_for_btn almeno una volta per renderlo sbloccante
    // (=> nodelay TRUE)
}

void GameRenderer::check_terminal_size(int width, int height) {
    if (width < GAME_WIDTH || height < GAME_HEIGHT) {
        std::cerr << "Terminal must be at least " << GAME_WIDTH << "x"
                  << GAME_HEIGHT << " current size: " << width << "x" << height
                  << std::endl;
        exit(EXIT_FAILURE);
    }
}

void GameRenderer::render_border() {
    // Stampa il bordo superiore
    mvhline(0, 1, ACS_HLINE, GAME_WIDTH - 2);

    // Stampa il bordo sinistro e destro
    mvvline(1, 0, ACS_VLINE, GAME_HEIGHT - 2);
    mvvline(1, GAME_WIDTH - 1, ACS_VLINE, GAME_HEIGHT - 2);

    // Stampa il bordo inferiore
    mvhline(GAME_HEIGHT - 1, 1, ACS_HLINE, GAME_WIDTH - 2);

    // Stampa gli angoli del bordo
    mvaddch(0, 0, ACS_ULCORNER);
    mvaddch(0, GAME_WIDTH - 1, ACS_URCORNER);
    mvaddch(GAME_HEIGHT - 1, 0, ACS_LLCORNER);
    mvaddch(GAME_HEIGHT - 1, GAME_WIDTH - 1, ACS_LRCORNER);
}

void GameRenderer::render_player() {
    render_str(player.get_last_position(), " ");  // cancello vecchio player
    render_str(player.get_position(), PLAYER_RENDER_CHARACTER);
}

void GameRenderer::render_floor() {
    for (int i = 0; i < GAME_WIDTH; i++) {
        render_str((Position){.x = i, .y = 1}, "_");
    }
}

void GameRenderer::clear_screen() { clear(); }

void GameRenderer::refresh_screen() { refresh(); }

int GameRenderer::translate_y(int y) const { return GAME_HEIGHT - y; };

Position GameRenderer::translate_position(Position position) const {
    return (Position){.x = position.x, .y = GAME_HEIGHT - position.y};
};

void GameRenderer::render_str(Position _position, const char* str) const {
    Position position = translate_position(_position);
    mvprintw(position.y, position.x, "%s", str);
};

void GameRenderer::render_str_num(Position position, const char* str,
                                  int number) const {
    render_str(position, str);
    attron(COLOR_PAIR(4));
    printw(" %d  ", number);
    attroff(COLOR_PAIR(4));
}

void GameRenderer::wait_for_btn(int btn) {
    nodelay(stdscr, FALSE);

    while (true) {
        int ch = getch();

        if (ch == (int)btn) {
            nodelay(stdscr, TRUE);
            return;
        }
    }
}

void GameRenderer::render() {
    render_player();
    render_floor();
    render_border();
    draw_floor();
    render_player_stats();
    refresh_screen();
}

void GameRenderer::render_2d_char_array(AsciiText text, Alignment h_align,
                                        Alignment v_align) {
    clear_screen();

    int y = text.height - 1;

    int text_length = (int)(strlen(text.text[0]));

    while (y >= 0) {
        int x = 0;
        if (h_align == Alignment::Center) {
            x = (GAME_WIDTH - text_length) / 2;
        } else if (h_align == Alignment::Right) {
            x = GAME_WIDTH - text_length;
        }

        int y_pos = 0;
        if (v_align == Alignment::Center) {
            y_pos = (GAME_HEIGHT - text.height) / 2;
        } else if (v_align == Alignment::Right) {
            y_pos = GAME_HEIGHT - text.height;
        }

        render_str((Position){.x = x, .y = y_pos + text.height - y},
                   text.text[y--]);

        // std::cout << correct_pos.x << " - " << correct_pos.y << std::endl;
    }

    refresh_screen();
    render_border();
}

void GameRenderer::rectangle(Position pos1, Position pos2) {
    mvhline(pos1.y, pos1.x, 0, pos2.x - pos1.x);
    mvhline(pos2.y, pos1.x, 0, pos2.x - pos1.x);
    mvvline(pos1.y, pos1.x, 0, pos2.y - pos1.y);
    mvvline(pos1.y, pos2.x, 0, pos2.y - pos1.y);
    mvaddch(pos1.y, pos1.x, ACS_ULCORNER);
    mvaddch(pos2.y, pos1.x, ACS_LLCORNER);
    mvaddch(pos1.y, pos2.x, ACS_URCORNER);
    mvaddch(pos2.y, pos2.x, ACS_LRCORNER);
}

void GameRenderer::draw_floor() {
    Position prev_native_pos = translate_position(
        (Position){.x = 0, .y = cur_level.get_cur_room().get_floor_at(0)});
    for (int i = 0; i < GAME_WIDTH; i++) {
        int cur_height = cur_level.get_cur_room().get_floor_at(i);
        int native_height = translate_y(cur_height);

        if (native_height == prev_native_pos.y && i != GAME_WIDTH - 1) continue;

        // forse solo i - 1, documentazione di merda
        mvhline(prev_native_pos.y, prev_native_pos.x + 1, ACS_HLINE,
                i - prev_native_pos.x - 1);

        // caso in cui non sei all'ultimo render ma c'e' differenza di altezza:
        // congiungi
        if (native_height != prev_native_pos.y) {
            auto m = std::min(prev_native_pos.y, native_height);
            auto M = std::max(prev_native_pos.y, native_height);
            mvvline(m + 1, i, ACS_VLINE, M - m - 1);

            // angoli
            if (prev_native_pos.y < native_height) {
                mvaddch(prev_native_pos.y, i, ACS_URCORNER);
                mvaddch(native_height, i, ACS_LLCORNER);
            } else {
                mvaddch(prev_native_pos.y, i, ACS_LRCORNER);
                mvaddch(native_height, i, ACS_ULCORNER);
            }
        }

        prev_native_pos = (Position){.x = i, .y = native_height};
    }
}

void GameRenderer::draw_vertical_line(int start_y, int end_y, int x) {
    int direction = (start_y < end_y) ? 1 : -1;

    for (int y = start_y; y != end_y; y += direction) {
        render_str((Position){.x = x, .y = y},
                   "x");  // disegna la linea verticale
    }
}

void GameRenderer::render_player_stats() {
    // render_str_num((Position){.x = 2, .y = GAME_HEIGHT - 1}, "on_floor",
    // (int)player.is_on_floor()); render_str_num((Position){.x = 15, .y =
    // GAME_HEIGHT - 1}, "on_ceiling", (int)player.is_touching_ceiling());
    render_str_num((Position){.x = 2, .y = GAME_HEIGHT - 1}, "delta_time",
                   (int)game_timer.get_delta_time_sec());
    render_str_num((Position){.x = 2, .y = GAME_HEIGHT - 2}, "w",
                   (int)input_manager.is_key_pressed('w'));
    render_str_num((Position){.x = 2, .y = GAME_HEIGHT - 3}, "a",
                   (int)input_manager.is_key_pressed('a'));
    render_str_num((Position){.x = 7, .y = GAME_HEIGHT - 2}, "s",
                   (int)input_manager.is_key_pressed('s'));
    render_str_num((Position){.x = 7, .y = GAME_HEIGHT - 3}, "d",
                   (int)input_manager.is_key_pressed('d'));
    render_str_num((Position){.x = 2, .y = GAME_HEIGHT - 4}, "rl",
                   (int)input_manager.is_key_pressed(1));
    render_str_num((Position){.x = 7, .y = GAME_HEIGHT - 4}, "rr",
                   (int)input_manager.is_key_pressed(4));

    render_str_num((Position){.x = 2, .y = GAME_HEIGHT - 9}, "is_on_floor",
                   (int)player.is_on_floor());
    render_str_num((Position){.x = 2, .y = GAME_HEIGHT - 10},
                   "is_touching_ceiling", (int)player.is_touching_ceiling());
    render_str_num((Position){.x = 2, .y = GAME_HEIGHT - 11},
                   "has_wall_on_left", (int)player.has_wall_on_left());
    render_str_num((Position){.x = 2, .y = GAME_HEIGHT - 12},
                   "has_wall_on_right", (int)player.has_wall_on_right());
    render_str_num((Position){.x = 2, .y = GAME_HEIGHT - 13}, "is_jumping",
                   (int)player.is_jumping);

    render_str_num((Position){.x = 2, .y = GAME_HEIGHT - 15}, "vel_x",
                   (int)player.vel_x);
    render_str_num((Position){.x = 2, .y = GAME_HEIGHT - 16}, "vel_y",
                   (int)player.vel_y);

    render_str_num((Position){.x = 2, .y = GAME_HEIGHT - 18}, "x",
                   (int)player.position.x);
    render_str_num((Position){.x = 2, .y = GAME_HEIGHT - 19}, "y",
                   (int)player.position.y);

    render_str_num(
        (Position){.x = 2, .y = GAME_HEIGHT - 21}, "floor[x]",
        (int)player.cur_level.get_cur_room().get_floor_at(player.position.x));
    render_str_num(
        (Position){.x = 2, .y = GAME_HEIGHT - 22}, "ceiling[x]",
        (int)player.cur_level.get_cur_room().get_floor_at(player.position.x));
}