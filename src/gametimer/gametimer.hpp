#ifndef _GAME_TIMER_HPP_
#define _GAME_TIMER_HPP_

#include <chrono>

#include <ncurses.h>
#include <chrono>
#include <iostream>

class GameTimer {
   private:
    float tick_interval;

   public:
    GameTimer(float tick_interval);
    void start();
    bool should_tick();

    // TODO sposta in private dopo debug
    std::chrono::time_point<std::chrono::high_resolution_clock> last_tick_time;
};

#endif  // _GAME_TIMER_HPP_