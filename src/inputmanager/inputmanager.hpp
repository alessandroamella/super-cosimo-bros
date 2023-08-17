#ifndef _INPUTMANAGER_HPP_
#define _INPUTMANAGER_HPP_

#include <ncurses.h>

class InputManager {
   public:
    InputManager();

    void process_input();

    bool is_key_pressed(int key) const;

   private:
    bool keys[256];  // Array per tenere traccia dei tasti premuti
};

#endif  // _INPUTMANAGER_HPP_