#ifndef _GAMERENDERER_HPP_
#define _GAMERENDERER_HPP_

#include <ncurses.h>

#include "../asciiart/texts.hpp"
#include "../gametimer/gametimer.hpp"
#include "../levelmanager/levelmanager.hpp"
#include "../list/list.hpp"
#include "../player/player.hpp"
#include "../shared/settings.hpp"

class GameRenderer {
   private:
    WINDOW* win;

    Player* player;
    LevelManager* level_manager;
    GameTimer* game_timer;

    void check_terminal_size(int width, int height);
    void render_border();
    void render_player_character(Position position);
    void render_player();
    void render_enemies();
    void render_powerups();
    void render_projectiles();
    void rectangle(Position pos1, Position pos2);
    void empty_rectangle(Position pos1, Position pos2);
    void render_floor();
    void render_platforms();
    void render_start_end_regions();
    void render_top_bar();
    void refresh_screen();
    void render_shop_items(List<Buyable>* items, int* currently_selected_index, int coins);
    void render_shop_top_bar(List<Buyable>* items, EntityType player_powerup);
    void render_shop_bottom_bar(int cur_rooms_completed, bool show_no_coins, bool show_bought);
    void pretty_print_coins(Position position, int amount);
    int translate_y(int y) const;
    Position translate_position(Position position) const;
    void render_str(Position position, const char* str) const;
    void render_debug_status();

   public:
    GameRenderer(Player* player, LevelManager* level_manager, GameTimer* timer);

    void initialize();
    void cleanup();

    void render_game();
    void render_shop(List<const char*> title, List<Buyable>* items, int* currently_selected_index, int coins, EntityType player_powerup, int cur_rooms_completed, bool show_no_coins, bool show_bought);

    void render_2d_char_array(List<const char*> text, Alignment h_align, Alignment v_align);
    void render_str_num(Position position, const char* str, int number) const;

    void clear_point(Position position);
    void clear_screen();

    WINDOW* get_win() const;
};

#endif  // _GAMERENDERER_HPP_