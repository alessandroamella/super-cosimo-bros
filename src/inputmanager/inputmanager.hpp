#ifndef _INPUTMANAGER_HPP_
#define _INPUTMANAGER_HPP_

#include <ncurses.h>

#define KEYS_ARR_LEN 128

class InputManager {
   public:
    InputManager();

    void read_input();

    bool is_key_pressed(int key) const;

   private:
    bool keys[KEYS_ARR_LEN];  // Array per tenere traccia dei tasti premuti
};

#endif  // _INPUTMANAGER_HPP_