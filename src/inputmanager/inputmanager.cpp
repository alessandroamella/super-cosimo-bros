#include "inputmanager.hpp"

#include <iostream>  // TODO debug

#include "../shared/functions.hpp"

InputManager::InputManager() {
    for (int i = 0; i < KEYS_ARR_LEN; ++i) {
        keys[i] = false;
    }
}

int last_ch = -1;
void InputManager::read_input() {
    int ch = getch();

    if (ch != ERR && !is_in(ch, 0, KEYS_ARR_LEN - 1))
        return;

    // aggiorna lo stato dei tasti
    if (last_ch == -1 || ch != last_ch) {
        for (int i = 0; i < KEYS_ARR_LEN; i++) {
            keys[i] = false;
        }
    }

    if (ch != ERR)
        keys[ch] = true;

    last_ch = ch;
}

bool InputManager::is_key_pressed(int key) const {
    return keys[key];
}