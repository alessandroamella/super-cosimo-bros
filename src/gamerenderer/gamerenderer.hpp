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
    void render_player();
    void render_enemies();
    void render_powerups();
    void rectangle(Position pos1, Position pos2);
    void empty_rectangle(Position pos1, Position pos2);
    void render_floor();
    void render_platforms();
    void render_start_end_regions();
    void render_top_bar();
    void refresh_screen();
    int translate_y(int y) const;
    Position translate_position(Position position) const;
    void render_str(Position position, const char* str) const;
    void render_debug_status();

   public:
    GameRenderer(Player* player, LevelManager* level_manager, GameTimer* timer);
    ~GameRenderer();

    void initialize();

    void render_all();

    void render_2d_char_array(List<const char*> text, Alignment h_align, Alignment v_align);
    void render_str_num(Position position, const char* str, int number) const;
    void clear_screen();

    WINDOW* get_win() const;
};

#endif  // _GAMERENDERER_HPP_