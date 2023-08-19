#include <chrono>

#include "gametimer.hpp"

GameTimer::GameTimer(float tick_interval)
    : tick_interval(tick_interval), last_tick_time(std::chrono::high_resolution_clock::now()) {}

void GameTimer::start() {
    last_tick_time = std::chrono::high_resolution_clock::now();
}

bool GameTimer::should_tick() {
    auto now = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> duration = now - last_tick_time;

    if (duration.count() >= tick_interval) {
        last_tick_time = now;
        return true;
    }

    return false;
}
