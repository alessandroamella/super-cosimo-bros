#ifndef _PROJECTILE_HPP_
#define _PROJECTILE_HPP_

#include <ncurses.h>

#include "../gametimer/gametimer.hpp"
#include "../inputmanager/inputmanager.hpp"
#include "../list/list.hpp"
#include "../platform/platform.hpp"
#include "../rigidentity/rigidentity.hpp"
#include "../shared/position.hpp"
#include "../shared/settings.hpp"

class Projectile : public RigidEntity {
   private:
    bool should_be_destroyed;
    EntityType shot_by;

   public:
    Projectile(GameTimer* timer, Position position, List<int>* floor, List<int>* ceiling, List<Platform>* platforms, EntityType shot_by);

    bool is_out_of_bounds();

    void start(Direction direction);
    void freeze();

    EntityType get_shot_by() const;

    // overrides
    void tick();
};

#endif  // _PROJECTILE_HPP_
