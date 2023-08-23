#ifndef _POWERUP_HPP_
#define _POWERUP_HPP_

#include "../shared/position.hpp"
#include "../staticbox/staticbox.hpp"

class Powerup : public StaticBox {
   protected:
    bool is_active;
    const char* render_char = "?";

   public:
    Powerup(Position position);
    bool get_is_active();
    void set_is_active(bool is_active);
    const char* get_render_char();
};

#endif  // _POWERUP_HPP_
