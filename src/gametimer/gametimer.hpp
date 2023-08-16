#ifndef _GAMETIMER_HPP_
#define _GAMETIMER_HPP_

#include <chrono>

class GameTimer {
   public:
    GameTimer();

    void start();
    void tick();
    bool should_tick() const;
    void reset_accumulator();
    float get_delta_time_sec() const;

   private:
    std::chrono::high_resolution_clock::time_point prev_time;
    float delta_time;
    const float tick_interval = 0.1f;  // ogni quanto deve fare tick
    float time_accumulator;
};

#endif  // _GAMETIMER_HPP_
