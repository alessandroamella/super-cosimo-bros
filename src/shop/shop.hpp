#ifndef _SHOP_HPP_
#define _SHOP_HPP_

#include "../inputmanager/inputmanager.hpp"
#include "../list/list.hpp"
#include "../player/player.hpp"
#include "../powerup/powerup.hpp"
#include "../shared/position.hpp"
#include "../shared/settings.hpp"

#include <ncurses.h>

class Shop {
   private:
    List<int> shop_controls;

    Player* player;
    InputManager* input_manager;
    List<Buyable> buyable_powerups;

    void buy_powerup(int powerup_index);

    int cur_index;

    bool should_show_no_coins_message;
    bool should_show_powerup_bought_message;
    bool should_apply_star;

   public:
    Shop(Player* player, InputManager* input_manager);

    List<int>* get_shop_controls();

    List<Buyable>* get_buyable_powerups_ptr();
    int* get_cur_index_ptr();

    void handle_key_press(int key_pressed);

    bool get_should_show_no_coins_message() const;
    bool get_should_show_powerup_bought_message() const;
    bool get_should_apply_star() const;
    void reset_shop_status();
};

#endif  // _SHOP_HPP_
