#include "gamerenderer.hpp"

#include <cstring>
#include <iostream>

GameRenderer::GameRenderer(Player& player) : player(player) {
}

GameRenderer::~GameRenderer() {
    endwin();  // Chiudi la finestra ncurses alla distruzione dell'oggetto
}

void GameRenderer::initialize() {
    int width, height;
    initscr();                        // Inizializza la finestra ncurses
    timeout(-1);                      // Disabilita timeout di getch
    cbreak();                         // Disabilita il buffering del tasto Invio
    raw();                            // Disabilita il buffer di input line-by-line
    keypad(stdscr, TRUE);             // Abilita la lettura dei tasti speciali
    noecho();                         // Non mostrare l'input utente
    curs_set(0);                      // Nascondi il cursore
    getmaxyx(stdscr, height, width);  // Imposta larghezza e altezza
    check_terminal_size(width, height);
    render_border();
}

void GameRenderer::check_terminal_size(int width, int height) {
    if (width < TERMINAL_WIDTH || height < TERMINAL_HEIGHT) {
        std::cerr << "Terminal must be at least " << TERMINAL_WIDTH << "x" << TERMINAL_HEIGHT << " current size: " << width << "x" << height << std::endl;
        exit(EXIT_FAILURE);
    }
}

void GameRenderer::render_border() {
    // Stampa il bordo superiore
    mvhline(0, 1, ACS_HLINE, TERMINAL_WIDTH - 2);

    // Stampa il bordo sinistro e destro
    mvvline(1, 0, ACS_VLINE, TERMINAL_HEIGHT - 2);
    mvvline(1, TERMINAL_WIDTH - 1, ACS_VLINE, TERMINAL_HEIGHT - 2);

    // Stampa il bordo inferiore
    mvhline(TERMINAL_HEIGHT - 1, 1, ACS_HLINE, TERMINAL_WIDTH - 2);

    // Stampa gli angoli del bordo
    mvaddch(0, 0, ACS_ULCORNER);
    mvaddch(0, TERMINAL_WIDTH - 1, ACS_URCORNER);
    mvaddch(TERMINAL_HEIGHT - 1, 0, ACS_LLCORNER);
    mvaddch(TERMINAL_HEIGHT - 1, TERMINAL_WIDTH - 1, ACS_LRCORNER);
    refresh_screen();
}

void GameRenderer::render_player() {
    render_str(player.get_position(), PLAYER_RENDER_CHARACTER);
}

void GameRenderer::render_floor() {
    for (int i = 0; i < TERMINAL_WIDTH; i++) {
        render_str((Position){.x = i, .y = 1}, "_");
    }
}

void GameRenderer::clear_screen() {
    clear();
}

void GameRenderer::refresh_screen() {
    refresh();
}

Position GameRenderer::translate_position(Position position) const {
    return (Position){.x = position.x, .y = TERMINAL_HEIGHT - position.y};
};

void GameRenderer::render_str(Position position, const char* str) const {
    mvprintw(position.y, position.x, str);
};

void GameRenderer::render() {
    render_player();
    render_floor();
    refresh_screen();
}

void GameRenderer::render_char_2darray(AsciiText text, Alignment h_align, Alignment v_align) {
    clear_screen();

    int y = text.height - 1;

    int text_length = (int)(strlen(text.text[0]));

    while (y >= 0) {
        int x = 0;
        if (h_align == Alignment::Center) {
            x = (TERMINAL_WIDTH - text_length) / 2;
        } else if (h_align == Alignment::Right) {
            x = TERMINAL_WIDTH - text_length;
        }

        int y_pos = 0;
        if (v_align == Alignment::Center) {
            y_pos = (TERMINAL_HEIGHT - text.height) / 2;
        } else if (v_align == Alignment::Right) {
            y_pos = TERMINAL_HEIGHT - text.height;
        }

        Position correct_pos = translate_position((Position){.x = x, .y = y_pos + text.height - y});
        render_str(correct_pos, text.text[y--]);

        // std::cout << correct_pos.x << " - " << correct_pos.y << std::endl;
    }

    refresh_screen();
    render_border();
}
