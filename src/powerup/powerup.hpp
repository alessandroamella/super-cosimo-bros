#include "../shared/position.hpp"

class Powerup {
   private:
    Position position;

   public:
    Powerup(Position position);
    Position get_position();
};