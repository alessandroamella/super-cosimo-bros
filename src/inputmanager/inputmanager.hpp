#ifndef _INPUTMANAGER_HPP_
#define _INPUTMANAGER_HPP_

#include <ncurses.h>

#define KEYS_ARR_LEN 128

class InputManager {
   public:
    InputManager();
    void read_input();
    void clear_input_buff();
    bool is_key_pressed(int key) const;
    char get_last_ch();

   private:
    int last_ch;
};

#endif  // _INPUTMANAGER_HPP_