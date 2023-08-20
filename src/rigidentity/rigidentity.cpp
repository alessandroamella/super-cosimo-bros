#include "rigidentity.hpp"

#include <iostream>

#include "../shared/functions.hpp"

RigidEntity::RigidEntity(GameTimer& timer,
                         Position position,
                         List<int> floor,
                         List<int> ceiling)
    : StaticEntity(position),
      game_timer(timer),
      starting_position(position),
      last_position(position),
      vel_x(RIGIDBODY_STARTING_VEL_X),
      vel_y(RIGIDBODY_STARTING_VEL_Y),
      floor(floor),
      ceiling(ceiling) {}

void RigidEntity::move_left() {
    vel_x = -PLAYER_WALK_VEL;
}

void RigidEntity::move_right() {
    vel_x = PLAYER_WALK_VEL;
}

void RigidEntity::apply_friction() {
    if (vel_x > 0)
        vel_x--;
    else if (vel_x < 0)
        vel_x++;
}

bool RigidEntity::is_on_floor() {
    return position.y - 1 <= floor.at(position.x);
}

bool RigidEntity::is_touching_ceiling() {
    return position.y - 1 >= ceiling.at(position.x);
}

bool RigidEntity::has_wall_on_left() {
    return position.x < 1 || floor.at(position.x - 1) > position.y + 1;
}

bool RigidEntity::has_wall_on_right() {
    return position.x >= GAME_WIDTH - 1 || position.y + 1 < floor.at(position.x);
}

void RigidEntity::clamp_position() {
    while (position.x < GAME_WIDTH - 1 && (position.x < 1.0f || has_wall_on_left() && vel_x < 0))
        position.x = (float)((int)position.x + 1);
    while (position.x > 1 && (position.x > GAME_WIDTH - 1 || has_wall_on_right() && vel_x > 0))
        position.x = (float)((int)position.x - 1);

    position.x = clamp(position.x, 1, GAME_WIDTH - 1);
    position.y = clamp(position.y, 1, GAME_HEIGHT - 1);

    if (is_on_floor())
        position.y = floor.at(position.x) + 1;
}

void RigidEntity::apply_gravity() {
    if (is_on_floor())
        vel_y = 0;
    else
        vel_y--;

    // se tocca il soffitto, la vel_y deve essere <= 0
    if (is_touching_ceiling())
        vel_y = clamp(vel_y, vel_y, 0);
};

void RigidEntity::move_based_on_vel() {
    position.x += vel_x /* * delta_time */;
    position.y += vel_y /* * delta_time */;
}

void RigidEntity::clamp_velocity() {
    vel_x = clamp(vel_x, -MAX_ABS_X_VEL, MAX_ABS_X_VEL);
    vel_y = clamp(vel_y, -MAX_ABS_Y_VEL, MAX_ABS_Y_VEL);

    if (has_wall_on_left() && vel_x < 0)
        vel_x = 0;
    else if (has_wall_on_right() && vel_x > 0)
        vel_x = 0;
}

void RigidEntity::reset_position() {
    position = starting_position;
}

void RigidEntity::tick() {
    Position cur_pos = position;

    apply_gravity();
    clamp_velocity();
    move_based_on_vel();
    clamp_position();

    last_position = cur_pos;
}

Position RigidEntity::get_last_position() {
    return last_position;
}
