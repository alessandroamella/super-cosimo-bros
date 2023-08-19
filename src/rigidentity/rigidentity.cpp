#include "rigidentity.hpp"

#include <iostream>
#include <string>  // TODO debug

#include "../shared/functions.hpp"

RigidEntity::RigidEntity(GameTimer& timer,
                         LevelManager& cur_level,
                         Position position)
    : StaticEntity(position),
      game_timer(timer),
      cur_level(cur_level),
      last_position(position),
      vel_x(RIGIDBODY_STARTING_VEL_X),
      vel_y(RIGIDBODY_STARTING_VEL_Y) {}

void RigidEntity::move_left() {
    vel_x = -3;
}

void RigidEntity::move_right() {
    vel_x = 3;
}

void RigidEntity::stop_moving() {
    if (vel_x > 0)
        vel_x--;
    else if (vel_x < 0)
        vel_x++;
}

bool RigidEntity::is_on_floor() {
    return position.y - 1 <= cur_level.get_cur_room().get_floor_at(position.x);
}

bool RigidEntity::is_touching_ceiling() {
    return position.y - 1 >=
           cur_level.get_cur_room().get_ceiling_at(position.x);
}

bool RigidEntity::has_wall_on_left() {
    // TODO < o <= 1?
    return position.x < 1 ||
           cur_level.get_cur_room().get_floor_at(position.x - 1) > position.y;
}

bool RigidEntity::has_wall_on_right() {
    // TODO < o <= 1?
    return position.x >= cur_level.get_cur_room().get_width() - 1 ||
           position.y < cur_level.get_cur_room().get_floor_at(position.x);
}

void RigidEntity::clamp_position() {
    while (has_wall_on_left() && vel_x < 0)
        position.x++;
    while (has_wall_on_right() && vel_x > 0)
        position.x--;

    position.x = clamp(position.x, 1, GAME_WIDTH - 1);
    position.y = clamp(position.y, 1, GAME_HEIGHT - 1);

    // TODO controlla se sul pavimento
    if (is_on_floor())
        position.y = cur_level.get_cur_room().get_floor_at(position.x) + 1;
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
