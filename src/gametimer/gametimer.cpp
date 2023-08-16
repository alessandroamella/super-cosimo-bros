#include "gametimer.hpp"

GameTimer::GameTimer() : delta_time(0.0f), time_accumulator(0.0f) {}

void GameTimer::start() {
    prev_time = std::chrono::high_resolution_clock::now();
}

void GameTimer::tick() {
    auto cur_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> duration = cur_time - prev_time;
    delta_time = duration.count();
    prev_time = cur_time;

    time_accumulator += delta_time;
}

bool GameTimer::should_tick() const {
    return time_accumulator >= tick_interval;
}

void GameTimer::reset_accumulator() {
    time_accumulator = 0.0f;
}

float GameTimer::get_delta_time_sec() const {
    return delta_time * 10000000.0f;
}