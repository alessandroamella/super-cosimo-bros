#include "platform.hpp"

#include "../shared/functions.hpp"
#include "../shared/settings.hpp"

Platform::Platform(Position ll, Position ur)
    : StaticBox(ll, ur) {
    if (ll.x > ur.x || ll.y > ur.y)
        throw std::invalid_argument("Platform: ll=" + ll.to_string() + " must be lower than ur=" + ur.to_string());
    else if (!is_in(ll.x, 0, GAME_WIDTH - 1))
        throw std::invalid_argument("Platform: ll.x=" + std::to_string(ll.x) + " must be in range [0, GAME_WIDTH-1=" + std::to_string(GAME_WIDTH - 1) + "]");
    else if (!is_in(ur.y, 0, GAME_HEIGHT - 5))
        throw std::invalid_argument("Platform: ur.y=" + std::to_string(ur.y) + " must be in range [0, GAME_HEIGHT-5=" + std::to_string(GAME_HEIGHT - 5) + "]");
}