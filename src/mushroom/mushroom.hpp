#ifndef _MUSHROOM_HPP_
#define _MUSHROOM_HPP_

#include "../powerup/powerup.hpp"
#include "../shared/position.hpp"

class Mushroom : public Powerup {
   private:
   public:
    Mushroom(Position position);
    EntityType get_entity_type() override;
};

#endif  // _MUSHROOM_HPP_
