#ifndef _SHARED_FUNCTIONS_HPP_
#define _SHARED_FUNCTIONS_HPP_

#include "../list/list.hpp"
#include "../powerup/powerup.hpp"
#include "../shared/settings.hpp"

int clamp(int n, int lower, int upper);
bool is_in(int n, int lower, int upper);
List<int> pick_random_points(int n, int lower, int upper);

template <typename Base, typename T>
inline bool instanceof (const T*) {
    return std::is_base_of<Base, T>::value;
}

Powerup* instance_random_powerup(Position position);

#endif  // _SHARED_FUNCTIONS_HPP_
