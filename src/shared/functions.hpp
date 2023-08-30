#ifndef _SHARED_FUNCTIONS_HPP_
#define _SHARED_FUNCTIONS_HPP_

#include "../list/list.hpp"
#include "../powerup/powerup.hpp"
#include "../shared/settings.hpp"

int clamp(int n, int lower, int upper);
bool is_in(int n, int lower, int upper);
List<int> pick_random_points(int n, int lower, int upper);

Powerup* instance_random_powerup(Position position);

#endif  // _SHARED_FUNCTIONS_HPP_
