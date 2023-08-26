#include "rigidentity.hpp"

#include <iostream>

#include "../shared/functions.hpp"

RigidEntity::RigidEntity(GameTimer* timer,
                         Position position,
                         List<int>* floor,
                         List<int>* ceiling,
                         List<Platform>* platforms)
    : StaticEntity(position),
      game_timer(timer),
      starting_position(position),
      last_position(position),
      vel_x(RIGIDBODY_STARTING_VEL_X),
      vel_y(RIGIDBODY_STARTING_VEL_Y),
      floor(floor),
      ceiling(ceiling),
      type(EntityType::RigidEntity),
      platforms(platforms),
      last_direction(Direction::Right) {}

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
    return position.y - 1 <= floor->at(position.x);
}

bool RigidEntity::is_touching_ceiling() {
    return position.y - 1 >= ceiling->at(position.x);
}

Position RigidEntity::get_after_pos() {
    return (Position){.x = position.x + vel_x, .y = position.y + vel_y};
}

bool RigidEntity::has_wall_on_left() {
    return position.x < 1 || floor->at(position.x - 1) > position.y;
}

bool RigidEntity::has_wall_on_right() {
    return position.x >= GAME_WIDTH - 1 || position.y < floor->at(position.x);
}

bool RigidEntity::is_on_platform() {
    for (int i = 0; i < platforms->length(); i++) {
        Platform& platform = platforms->at(i);

        if (platform.is_on_top(position))
            return true;
    }

    return false;
}

void RigidEntity::clamp_position() {
    position.x = clamp(position.x, 1, GAME_WIDTH - 1);
    position.y = clamp(position.y, 1, GAME_HEIGHT - 1);

    while (has_wall_on_left() && vel_x >= 0 && position.x < GAME_WIDTH - 1) {
        position.x++;
    }
    while (has_wall_on_right() && vel_x <= 0 && position.x > 1) {
        position.x--;
    }

    position.x = clamp(position.x, 1, GAME_WIDTH - 1);
    position.y = clamp(position.y, 1, GAME_HEIGHT - 1);

    if (is_on_floor())
        position.y = floor->at(position.x) + 1;
}

void RigidEntity::apply_gravity() {
    // if (is_jumping)
    //     update_jump_position();
    if (is_on_floor() || is_on_platform())
        vel_y = std::max(0, vel_y);
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

bool RigidEntity::collides_with_platform() {
    for (int i = 0; i < platforms->length(); i++) {
        Platform& platform = platforms->at(i);
        Position after_pos = get_after_pos();

        if (platform.is_inside(after_pos))
            return true;
        else if (platform.is_x_within(position.x) && platform.get_top_y(position.x) == position.y - 1 && (!platform.is_x_within(after_pos.x) || platform.get_top_y(after_pos.x) != after_pos.y - 1)) {
            // check for adjacent platform
            bool adjacent_platform = false;

            for (int j = 0; j < platforms->length(); j++) {
                Platform& _platform = platforms->at(j);

                if (_platform.is_x_within(after_pos.x) && _platform.get_top_y(after_pos.x) == position.y - 1)
                    adjacent_platform = true;
            }

            if (!adjacent_platform)
                return true;
        }
    }

    return false;
}

void RigidEntity::clamp_velocity() {
    vel_x = clamp(vel_x, -MAX_ABS_X_VEL, MAX_ABS_X_VEL);
    vel_y = clamp(vel_y, MAX_FALL_VEL, MAX_JUMP_VEL);

    // non toccare se vel_x == 0
    if (vel_x > 0)
        last_direction = Direction::Right;
    else if (vel_x < 0)
        last_direction = Direction::Left;

    while (vel_x >= 0 && (position.x + vel_x >= GAME_WIDTH - 1 || floor->at(position.x + vel_x) > position.y))
        vel_x--;
    while (vel_x <= 0 && (position.x + vel_x <= 1 || floor->at(position.x + vel_x - 1) > position.y))
        vel_x++;

    if (has_wall_on_left() && vel_x < 0)
        vel_x = 0;
    else if (has_wall_on_right() && vel_x > 0)
        vel_x = 0;
}

Position RigidEntity::get_velocity() {
    return (Position){.x = vel_x, .y = vel_y};
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

Direction RigidEntity::get_direction() {
    return last_direction;
}

bool RigidEntity::is_out_of_bounds() {
    return !is_in(position.x, 1, GAME_WIDTH - 1) || !is_in(position.y, 1, GAME_HEIGHT - 1);
}

Position RigidEntity::get_last_position() {
    return last_position;
}
