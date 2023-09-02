#ifndef _ENEMY_HPP_
#define _ENEMY_HPP_

#include <ncurses.h>

#include "../gametimer/gametimer.hpp"
#include "../inputmanager/inputmanager.hpp"
#include "../list/list.hpp"
#include "../platform/platform.hpp"
#include "../rigidentity/rigidentity.hpp"
#include "../shared/position.hpp"
#include "../shared/settings.hpp"

class Enemy : public RigidEntity {
   private:
    int health;
    bool is_dead;

    bool should_change_direction();
    void change_direction();

    bool has_wall_on_left();
    bool has_wall_on_right();
    bool has_pit();

    std::chrono::steady_clock::time_point next_projectile_delay;

   public:
    Enemy(Position position, List<int>* floor, List<int>* ceiling, List<Platform>* platforms);

    int get_health();
    void remove_health();

    void start_walking();
    void stop_walking();

    bool should_shoot();
    void reset_shoot();

    bool get_is_dead();
    void set_is_dead(bool is_dead);

    // overrides
    void tick();
};

#endif  // _ENEMY_HPP_
