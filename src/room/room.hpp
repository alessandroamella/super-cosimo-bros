#ifndef _ROOM_HPP_
#define _ROOM_HPP_

#include "../enemy/enemy.hpp"
#include "../gametimer/gametimer.hpp"
#include "../list/list.hpp"
#include "../platform/platform.hpp"
#include "../powerup/powerup.hpp"
#include "../shared/position.hpp"
#include "../shared/settings.hpp"

class Room {
   private:
    int width;
    int height;

    List<int> floor;
    List<int> ceiling;
    List<Platform> platforms;

    List<Powerup*> powerups;
    List<Enemy> enemies;

    StaticBox start_region;
    StaticBox end_region;

   public:
    Room(List<Powerup*> powerups, List<int> floor, List<int> ceiling, List<Platform> platforms, int width, int height, StaticBox start_region, StaticBox end_region);

    int get_floor_at(int x);
    int get_ceiling_at(int x);
    int get_platform_at(int x);

    List<int>& get_floor();
    List<int>& get_ceiling();

    List<Platform>& get_platforms();

    int get_width();
    int get_height();

    void add_enemy(Enemy enemy);

    List<Powerup*>& get_powerups();
    List<Enemy>& get_enemies();

    StaticBox& get_start_region();
    StaticBox& get_end_region();

    Position get_player_start_position();

    bool is_within_bounds(Position position);

    void load();
    void freeze();

    void tick();
};

#endif  // _ROOM_HPP_
