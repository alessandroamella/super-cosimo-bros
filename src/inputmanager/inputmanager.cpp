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
    List<int> btns = List<int>();
    btns.push(btn);
    wait_for_btns(win, btns);
}

int InputManager::wait_for_btns(WINDOW* win, List<int> btn) {
    nodelay(win, false);

    while (true) {
        int ch = wgetch(win);

        if (btn.contains(ch)) {
            nodelay(win, true);
            return ch;
        }
    }

    return -1;
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
