#ifndef _ASCII_TEXTS_HPP_
#define _ASCII_TEXTS_HPP_

#include "../list/list.hpp"

enum class Alignment {
    Beginning,
    Center,
    End
};

class AsciiTexts {
   private:
    List<const char*> splash;
    List<const char*> game_over;
    List<const char*> shop;

    List<const char*> read_from_file(const char* file_name);

   public:
    AsciiTexts();
    List<const char*>& get_splash();
    List<const char*>& get_game_over();
    List<const char*>& get_shop();
};

#endif  // _ASCII_TEXTS_HPP_
