#ifndef _RIGIDENTITY_HPP_
#define _RIGIDENTITY_HPP_

#include <ncurses.h>

#include "../gametimer/gametimer.hpp"
#include "../list/list.hpp"
#include "../shared/position.hpp"
#include "../shared/settings.hpp"
#include "../staticentity/staticentity.hpp"

class RigidEntity : public StaticEntity {
   protected:
    GameTimer& game_timer;

    List<int> floor;
    List<int> ceiling;

    Position starting_position;

    void apply_gravity();
    void move_based_on_vel();

    void move_left();
    void move_right();
    void apply_friction();
    void clamp_position();
    void clamp_velocity();

   public:
    RigidEntity(GameTimer& timer, Position position, List<int> floor, List<int> ceiling);
    Position get_last_position();
    void reset_position();
    void tick();

    // TODO finito il debug, sposta in private
    bool is_on_floor();
    bool is_touching_ceiling();
    bool has_wall_on_left();
    bool has_wall_on_right();
    int vel_x;
    int vel_y;
    Position last_position;
};

#endif  // _RIGIDENTITY_HPP_
