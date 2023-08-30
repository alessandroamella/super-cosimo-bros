#ifndef _RIGIDENTITY_HPP_
#define _RIGIDENTITY_HPP_

#include <ncurses.h>

#include "../gametimer/gametimer.hpp"
#include "../list/list.hpp"
#include "../platform/platform.hpp"
#include "../shared/position.hpp"
#include "../shared/settings.hpp"
#include "../staticentity/staticentity.hpp"

class RigidEntity : public StaticEntity {
   protected:
    EntityType type;

    GameTimer* game_timer;

    List<int>* floor;
    List<int>* ceiling;

    Position starting_position;

    List<Platform>* platforms;

    Direction last_direction;

    void apply_gravity();
    void move_based_on_vel();

    bool collides_with_platform();

    void move_left();
    void move_right();
    void apply_friction();
    void clamp_position();
    void clamp_velocity();

    bool is_on_floor();
    bool is_touching_ceiling();
    Position get_after_pos();
    bool has_wall_on_left();
    bool has_wall_on_right();
    bool is_on_platform();
    int vel_x;
    int vel_y;
    Position last_position;

   public:
    RigidEntity(GameTimer* timer, Position position, List<int>* floor, List<int>* ceiling, List<Platform>* platforms);
    Position get_last_position();
    void reset_position();
    Position get_velocity();
    void tick();

    Direction get_direction();

    bool is_out_of_bounds();
};

#endif  // _RIGIDENTITY_HPP_
