#ifndef _INPUTMANAGER_HPP_
#define _INPUTMANAGER_HPP_

#include <ncurses.h>

#include "../list/list.hpp"

#define KEYS_ARR_LEN 128

class InputManager {
   private:
    int last_ch;

   public:
    InputManager();
    void read_input(WINDOW* win);
    void wait_for_btn(WINDOW* win, int btn);
    int wait_for_btns(WINDOW* win, List<int> btn);
    void clear_input_buff();
    bool is_key_pressed(int key) const;
    char get_last_ch();
};

#endif  // _INPUTMANAGER_HPP_