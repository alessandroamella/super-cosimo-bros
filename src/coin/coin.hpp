#ifndef _COIN_HPP_
#define _COIN_HPP_

#include "../powerup/powerup.hpp"
#include "../shared/position.hpp"

class Coin : public Powerup {
   private:
    int value;

   public:
    Coin(Position position, int value);
    int get_value();
    int get_digits();

    static int generate_random_coin_value();

    const char* get_render_char() override;
    EntityType get_entity_type() override;
};

#endif  // _COIN_HPP_
