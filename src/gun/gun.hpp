#ifndef _GUN_HPP_
#define _GUN_HPP_

#include "../powerup/powerup.hpp"
#include "../shared/position.hpp"

class Gun : public Powerup {
   private:
    const char* render_char = "P";

   public:
    Gun(Position position);
    const char* get_render_char() override;
    EntityType get_entity_type() override;
};

#endif  // _GUN_HPP_
