#ifndef _ROOM_HPP_
#define _ROOM_HPP_

#include "../enemy/enemy.hpp"
#include "../list/list.hpp"
#include "../platform/platform.hpp"
#include "../powerup/powerup.hpp"
#include "../projectile/projectile.hpp"
#include "../shared/position.hpp"
#include "../shared/settings.hpp"

class Room {
   private:
    int width;
    int height;

    const int room_id;

    List<int> floor;
    List<int> ceiling;
    List<Platform> platforms;

    List<Powerup*> powerups;
    List<Enemy> enemies;
    List<Projectile*> projectiles;

    StaticBox start_region;
    StaticBox end_region;

   public:
    Room(const int room_id, List<int> floor, List<int> ceiling, List<Platform> platforms, int width, int height, StaticBox start_region, StaticBox end_region);
    Room(const Room& base);  // costruttore copia
    Room* clone() const;

    int get_room_id();

    int get_floor_at(int x);
    int get_ceiling_at(int x);
    Platform* get_platform_at(int x);

    List<int>& get_floor();
    List<int>& get_ceiling();

    List<Platform>& get_platforms();

    int get_width();
    int get_height();

    List<Powerup*>& get_powerups();
    List<Enemy>& get_enemies();
    List<Projectile*>& get_projectiles();

    void add_enemy(Enemy enemy);
    void add_powerup(Powerup* powerup);
    void add_projectile(Projectile* projectile);

    void remove_projectile(Projectile* projectile);

    StaticBox& get_start_region();
    StaticBox& get_end_region();

    Position get_player_start_position();

    void load();
    void freeze();

    void cleanup();

    void tick();
};

#endif  // _ROOM_HPP_
