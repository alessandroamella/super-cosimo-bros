#include "projectile.hpp"
#include "../shared/functions.hpp"

Projectile::Projectile(Position position, List<int>* floor, List<int>* ceiling, List<Platform>* platforms, EntityType shot_by)
    : RigidEntity(position, floor, ceiling, platforms),
      shot_by(shot_by),
      should_be_destroyed(false) {}

bool Projectile::is_out_of_bounds() {
    // 2 al posto di 1 cosi' quando clampo a [1, GAME_WIDTH - 1] non da errori ma lo stesso restituisce che e' out of bounds
    return should_be_destroyed || !is_in(position.x, 2, GAME_WIDTH - 2) || !is_in(position.y, 2, GAME_HEIGHT - 2);
}

void Projectile::start(Direction direction) {
    vel_x = direction == Direction::Left ? -PROJECTILE_VEL : PROJECTILE_VEL;
}

void Projectile::freeze() {
    vel_x = 0;
}

EntityType Projectile::get_shot_by() const {
    return shot_by;
}

void Projectile::tick() {
    if (is_out_of_bounds()) {
        should_be_destroyed = true;
        return;
    }

    Position cur_pos = position;

    move_based_on_vel();

    if (is_out_of_bounds() || has_wall_on_left() || has_wall_on_right() || collides_with_platform())
        should_be_destroyed = true;

    position.x = clamp(position.x, 1, GAME_WIDTH - 1);
    position.y = clamp(position.y, 1, GAME_HEIGHT - 1);

    last_position = cur_pos;
}