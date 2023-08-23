#ifndef _COIN_HPP_
#define _COIN_HPP_

#include "../powerup/powerup.hpp"
#include "../shared/position.hpp"

class Coin : public Powerup {
   private:
    int value;

   public:
    Coin(Position position, int value);
    EntityType get_entity_type();
    const char* get_render_char();
    int get_value();
};

#endif  // _COIN_HPP_
