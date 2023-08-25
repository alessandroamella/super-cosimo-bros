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
    if (a_rigid != nullptr) {
        auto a_vel = a_rigid->get_velocity();

        // check if a_rigid position + a_vel collides with b
        Position a_pos_plus_vel = {a_pos.x + a_vel.x, a_pos.y + a_vel.y};

        bool collides_with_vel = is_in(b_pos.x, a_pos.x, a_pos_plus_vel.x) && is_in(b_pos.y, a_pos.y, a_pos_plus_vel.y);
        if (collides_with_vel)
            return true;
    }

    return false;
}