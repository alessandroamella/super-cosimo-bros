#ifndef _ENEMY_HPP_
#define _ENEMY_HPP_

#include <ncurses.h>

#include "../gametimer/gametimer.hpp"
#include "../inputmanager/inputmanager.hpp"
#include "../list/list.hpp"
#include "../rigidentity/rigidentity.hpp"
#include "../shared/position.hpp"
#include "../shared/settings.hpp"

class Enemy : public RigidEntity {
   private:
    int health;

    bool should_change_direction();
    void change_direction();

   public:
    Enemy(GameTimer& timer, Position position, List<int> floor, List<int> ceiling);

    int get_health();
    void remove_health();

    void start_walking();
    void stop_walking();

    // overrides
    void tick();

    // TODO sposta in private dopo debug
    bool has_wall_on_left();
    bool has_wall_on_right();
    bool has_pit_on_left();
    bool has_pit_on_right();
};

#endif  // _ENEMY_HPP_
