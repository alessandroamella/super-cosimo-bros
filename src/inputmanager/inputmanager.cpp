#include "inputmanager.hpp"

InputManager::InputManager() {
    initscr();
    raw();
    keypad(stdscr, TRUE);
    noecho();
    curs_set(0);

    for (int i = 0; i < 256; ++i) {
        keys[i] = false;
    }
}

InputManager::~InputManager() {
    endwin();
}

void InputManager::process_input() {
    int ch = getch();

    // aggiorna lo stato dei tasti
    for (int i = 0; i < 256; ++i) {
        keys[i] = false;
    }
    keys[ch] = true;
}

bool InputManager::is_key_pressed(int key) const {
    return keys[key];
}