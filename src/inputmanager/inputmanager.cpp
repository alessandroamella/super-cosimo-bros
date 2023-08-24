#include "inputmanager.hpp"
#include "../shared/functions.hpp"

#include <ncurses.h>

InputManager::InputManager()
    : last_ch(ERR) {}

void InputManager::read_input(WINDOW* win) {
    int ch = wgetch(win);

    // mvprintw(1, 25, "CHAR: %c  ", (int)ch);

    if (is_in(ch, 0, KEYS_ARR_LEN - 1))
        last_ch = ch;
}

void InputManager::wait_for_btn(WINDOW* win, int btn) {
    nodelay(win, FALSE);

    while (true) {
        int ch = wgetch(win);

        if (ch == (int)btn) {
            nodelay(win, TRUE);
            return;
        }
    }
}

void InputManager::clear_input_buff() {
    last_ch = ERR;
}

bool InputManager::is_key_pressed(int key) const {
    return last_ch == key;
}

char InputManager::get_last_ch() {
    return last_ch;
}
