#ifndef _GAMERENDERER_HPP_
#define _GAMERENDERER_HPP_

#include <ncurses.h>

#include "../asciiart/asciitext.hpp"
#include "../player/player.hpp"
#include "../shared/settings.hpp"

class GameRenderer {
   private:
    Player& player;

    void check_terminal_size(int width, int height);
    void render_border();
    void render_player();
    void render_floor();
    void refresh_screen();
    Position translate_position(Position position) const;
    void render_str(Position position, const char* str) const;
    void rectangle(Position pos1, Position pos2);

   public:
    GameRenderer(Player& player);
    ~GameRenderer();

    void initialize();
    void render();
    void render_2d_char_array(AsciiText text, Alignment h_align, Alignment v_align);
    void render_str_num(Position position, const char* str, int number) const;
    void wait_for_btn(int btn);
    void clear_screen();
};

#endif  // _GAMERENDERER_HPP_