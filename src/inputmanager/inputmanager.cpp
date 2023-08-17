#include "inputmanager.hpp"

InputManager::InputManager() {
    for (int i = 0; i < 256; ++i) {
        keys[i] = false;
    }
}

void InputManager::read_input() {
    int ch = getch();

    // if (ch == ERR) return;  // TODO! serve?
    // aggiorna lo stato dei tasti
    for (int i = 0; i < 256; ++i) {
        keys[i] = false;
    }
    keys[ch] = true;
}

bool InputManager::is_key_pressed(int key) const {
    return keys[key];
}