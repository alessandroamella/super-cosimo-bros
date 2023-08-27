#include "shop.hpp"

#include "../shared/functions.hpp"

Shop::Shop(Player* player, InputManager* input_manager)
    : player(player),
      buyable_powerups(),
      input_manager(input_manager),
      cur_index(0),
      shop_controls(),
      should_show_no_coins_message(false),
      should_show_powerup_bought_message(false),
      should_apply_star(false) {
    buyable_powerups.push({.type = EntityType::Heart, .symbol = '+', .name = "Cuore", .price = 10});
    buyable_powerups.push({.type = EntityType::Mushroom, .symbol = '&', .name = "Fungo", .price = 15});
    buyable_powerups.push({.type = EntityType::Star, .symbol = 'S', .name = "Stella", .price = 35});
    buyable_powerups.push({.type = EntityType::Gun, .symbol = 'P', .name = "Pistola", .price = 40});

    shop_controls.push((int)ShopControls::Left);
    shop_controls.push((int)ShopControls::Right);
    shop_controls.push((int)ShopControls::Buy);
    shop_controls.push((int)ShopControls::Quit);
}

void Shop::handle_key_press(int key_pressed) {
    switch (key_pressed) {
        case (int)ShopControls::Left:
            cur_index--;
            break;
        case (int)ShopControls::Right:
            cur_index++;
            break;
        case (int)ShopControls::Buy:
            buy_powerup(cur_index);
            break;
    }

    cur_index = clamp(cur_index, 0, buyable_powerups.length() - 1);
}

bool Shop::get_should_show_no_coins_message() const {
    return should_show_no_coins_message;
}

bool Shop::get_should_show_powerup_bought_message() const {
    return should_show_powerup_bought_message;
}

bool Shop::get_should_apply_star() const {
    return should_apply_star;
}

void Shop::reset_shop_status() {
    should_show_no_coins_message = false;
    should_show_powerup_bought_message = false;
    should_apply_star = false;
}

List<int>* Shop::get_shop_controls() {
    return &shop_controls;
}

List<Buyable>* Shop::get_buyable_powerups_ptr() {
    return &buyable_powerups;
}

int* Shop::get_cur_index_ptr() {
    return &cur_index;
}

void Shop::buy_powerup(int powerup_index) {
    Buyable powerup = buyable_powerups.at(powerup_index);
    if (player->get_coins() >= powerup.price) {
        player->remove_coins(powerup.price);

        switch (powerup.type) {
            case EntityType::Heart:
                player->add_health(HEART_HEALTH_INCREASE);
                break;
            case EntityType::Star:
                player->add_star();
                should_apply_star = true;
            default:
                player->set_powerup_type(powerup.type);
                break;
        }

        should_show_powerup_bought_message = true;
        should_show_no_coins_message = false;
    } else {
        should_show_no_coins_message = true;
        should_show_powerup_bought_message = false;
    }
}
