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

    GameTimer& game_timer;

    List<int> floor;
    List<int> ceiling;
    List<Platform> platforms;

    List<Powerup> powerups;
    List<Enemy> enemies;

   public:
    Room(GameTimer& timer, List<int> floor, List<int> ceiling, List<Platform> platforms, int width, int height);

    int get_floor_at(int x);
    int get_ceiling_at(int x);

    List<Platform>& get_platforms();

    int get_width();
    int get_height();

    List<Powerup>& get_powerups();
    List<Enemy>& get_enemies();

    bool is_within_bounds(Position position);
    void place_enemies_randomly(int enemy_count, int start_padding);

    void load();
    void freeze();

    void tick();
};

#endif  // _ROOM_HPP_
