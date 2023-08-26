#include "hitbox.hpp"

#include "../rigidentity/rigidentity.hpp"
#include "../shared/functions.hpp"
#include "../shared/settings.hpp"

bool collides(StaticEntity* a, StaticEntity* b) {
    Position a_pos = a->get_position();
    Position b_pos = b->get_position();

    bool collides_directly = a_pos.x == b_pos.x && a_pos.y == b_pos.y;
    if (collides_directly)
        return true;

    RigidEntity* a_rigid = dynamic_cast<RigidEntity*>(a);
    RigidEntity* b_rigid = dynamic_cast<RigidEntity*>(b);

    Position a_vel = a_rigid != nullptr ? a_rigid->get_velocity() : (Position){.x = 0, .y = 0};
    Position b_vel = b_rigid != nullptr ? b_rigid->get_velocity() : (Position){.x = 0, .y = 0};

    // check if a_rigid position + a_vel collides with b
    Position a_pos_plus_vel = {a_pos.x + a_vel.x, a_pos.y + a_vel.y};
    Position b_pos_plus_vel = {b_pos.x + b_vel.x, b_pos.y + b_vel.y};

    // check collisions using is_in
    bool collides_with_vel_a = is_in(a_pos_plus_vel.x, std::min(b_pos.x, b_pos_plus_vel.x), std::max(b_pos.x, b_pos_plus_vel.x)) &&
                               is_in(a_pos_plus_vel.y, std::min(b_pos.y, b_pos_plus_vel.y), std::max(b_pos.y, b_pos_plus_vel.y));
    bool collides_with_vel_b = is_in(b_pos_plus_vel.x, std::min(a_pos.x, a_pos_plus_vel.x), std::max(a_pos.x, a_pos_plus_vel.x)) &&
                               is_in(b_pos_plus_vel.y, std::min(a_pos.y, a_pos_plus_vel.y), std::max(a_pos.y, a_pos_plus_vel.y));

    return collides_with_vel_a || collides_with_vel_b;
}