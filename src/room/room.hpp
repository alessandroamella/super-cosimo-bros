#ifndef _ROOM_HPP_
#define _ROOM_HPP_

#include "../list/list.hpp"
#include "../player/player.hpp"
#include "../powerup/powerup.hpp"
#include "../shared/position.hpp"
#include "../shared/settings.hpp"

class Room {
   public:
    Room(List<int> floor);
    void load();
    int get_floor_at(int x);
    int get_ceiling_at(int x);

   private:
    List<int> floor;

    List<Powerup> powerups;
    // List<Enemy> enemies;
    // List<Projectile> projectiles;
    // List<Platform> platforms;
};

#endif  // _ROOM_HPP_
