#include "rate_limiter.hpp"

RateLimiter::RateLimiter(double rate_limit_hz, double earliness_leniency_seconds)
    : rate_limit_duration(1.0 / rate_limit_hz), earliness_leniency_duration(earliness_leniency_seconds),
      last_cycle_time(std::chrono::steady_clock::now() -
                      std::chrono::duration_cast<std::chrono::steady_clock::duration>(rate_limit_duration)) {}

double RateLimiter::get_last_processed_time() const { return last_processed_time; }

bool RateLimiter::attempt_to_run() {
    auto now = std::chrono::steady_clock::now();
    auto elapsed_time_since_last_run = now - last_cycle_time;

    auto shortest_required_duration = rate_limit_duration - earliness_leniency_duration;

    if (elapsed_time_since_last_run >= shortest_required_duration) { // A
        if (not ran_during_cycle) {
            ran_during_cycle = true;
            return true;
        }
    }

    if (elapsed_time_since_last_run >= rate_limit_duration) { // B
        // start of a new cycle
        last_cycle_time = now;
        ran_during_cycle = false;
        // we don't need to return true here because  B => A
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
