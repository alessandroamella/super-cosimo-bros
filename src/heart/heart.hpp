#ifndef _HEART_HPP_
#define _HEART_HPP_

#include "../powerup/powerup.hpp"
#include "../shared/position.hpp"

class Heart : public Powerup {
   private:
    const char* render_char = "+";

   public:
    Heart(Position position);
    EntityType get_entity_type();
    const char* get_render_char();
};

#endif  // _HEART_HPP_
