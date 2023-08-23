#ifndef _STAR_HPP_
#define _STAR_HPP_

#include "../powerup/powerup.hpp"
#include "../shared/position.hpp"

class Star : public Powerup {
   private:
   public:
    Star(Position position);
    EntityType get_entity_type();
};

#endif  // _STAR_HPP_
