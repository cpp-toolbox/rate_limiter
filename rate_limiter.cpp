#include "rate_limiter.hpp"

RateLimiter::RateLimiter(double rate_limit_hz)
    : rate_limit_duration(1.0 / rate_limit_hz),
      last_run_time(std::chrono::steady_clock::now() -
                    std::chrono::duration_cast<std::chrono::steady_clock::duration>(rate_limit_duration)) {}

double RateLimiter::get_last_processed_time() const { return last_processed_time; }

bool RateLimiter::attempt_to_run() {
    auto now = std::chrono::steady_clock::now();
    if (now - last_run_time >= rate_limit_duration) {
        last_processed_time = std::chrono::duration<double>(now - last_run_time).count(); // store time in seconds
        last_run_time = now;
        return true;
    }
    return false;
}

bool RateLimiter::attempt_to_run(double delta_time) {
    manual_time_processed_since_last_tick += delta_time;
    if (manual_time_processed_since_last_tick >= rate_limit_duration.count()) {
        last_processed_time = manual_time_processed_since_last_tick; // store processed time in seconds
        manual_time_processed_since_last_tick = 0.0;                 // should we do subtraction?
        return true;
    }
    return false;
}

void RateLimiter::change_rate_limit(double rate_limit_hz) {
    rate_limit_duration = std::chrono::duration<double>(1.0 / rate_limit_hz);
}
