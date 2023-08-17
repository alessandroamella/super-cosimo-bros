#ifndef _GAMERENDERER_HPP_
#define _GAMERENDERER_HPP_

#include <ncurses.h>

#include "../asciiart/asciitext.hpp"
#include "../player/player.hpp"

#define TERMINAL_WIDTH 130
#define TERMINAL_HEIGHT 40

class GameRenderer {
   private:
    Player& player;

    void check_terminal_size(int width, int height);
    void render_border();
    void render_player();
    void render_floor();
    void clear_screen();
    void refresh_screen();
    Position translate_position(Position position) const;
    void render_str(Position position, const char* str) const;

    /** translate_coordinates: y=0 significa in alto => la y deve essere "mappata" al contrario */
    /** render_char: wrapper di mvprintw */

   public:
    GameRenderer(Player& player);
    ~GameRenderer();

    void initialize();
    void render();
    void render_char_2darray(AsciiText text, Alignment h_align, Alignment v_align);
};

#endif  // _GAMERENDERER_HPP_