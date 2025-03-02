#include "rate_limiter.hpp"

RateLimiter::RateLimiter(double rate_limit_hz)
    : rate_limit_duration(1.0 / rate_limit_hz),
      last_run_time(std::chrono::steady_clock::now() -
                    std::chrono::duration_cast<std::chrono::steady_clock::duration>(rate_limit_duration)) {}

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
    if (manual_time_processed_since_last_tick >= rate_limit_duration.count()) {
        manual_time_processed_since_last_tick = 0.0;
        return true;
    }
    return false;
}

void RateLimiter::change_rate_limit(double rate_limit_hz) {
    rate_limit_duration = std::chrono::duration<double>(1.0 / rate_limit_hz);
}
