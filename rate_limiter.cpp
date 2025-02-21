#include "rate_limiter.hpp"

RateLimiter::RateLimiter(int rate_limit_hz)
    : rate_limit_duration(std::chrono::milliseconds(1000 / rate_limit_hz)),
      last_run_time(std::chrono::steady_clock::now() - rate_limit_duration) {}

bool RateLimiter::attempt_to_run() {
    auto now = std::chrono::steady_clock::now();
    if (now - last_run_time >= rate_limit_duration) {
        last_run_time = now;
        return true;
    }
    return false;
}

bool RateLimiter::attempt_to_run(double delta_time) {
    manual_time_processed_since_last_tick += delta_time;
    if (manual_time_processed_since_last_tick >= rate_limit_duration.count() / 1000.0) {
        manual_time_processed_since_last_tick = 0.0;
        return true;
    }
    return false;
}

void RateLimiter::change_rate_limit(int rate_limit_hz) {
    rate_limit_duration = std::chrono::milliseconds(1000 / rate_limit_hz);
}
