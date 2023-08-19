#ifndef _ROOM_HPP_
#define _ROOM_HPP_

#include "../list/list.hpp"
#include "../powerup/powerup.hpp"
#include "../shared/position.hpp"
#include "../shared/settings.hpp"

class Room {
   public:
    Room(List<int> floor, int width, int height);
    void load();
    int get_floor_at(int x);
    int get_ceiling_at(int x);
    int get_width();
    int get_height();
    bool is_within_bounds(Position position);

   private:
    List<int> floor;
    int width;
    int height;

    List<Powerup> powerups;
    // List<Enemy> enemies;
    // List<Projectile> projectiles;
    // List<Platform> platforms;
};

#endif  // _ROOM_HPP_
