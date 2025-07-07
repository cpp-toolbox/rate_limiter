#ifndef RATELIMITER_HPP
#define RATELIMITER_HPP

#include <chrono>

#include "sbpt_generated_includes.hpp"

class RateLimiter {
  public:
    explicit RateLimiter(double rate_limit_hz, double earliness_leniency_seconds = 0.0);

    ConsoleLogger logger{"rate_limiter"};

    bool attempt_to_run();
    bool attempt_to_run(double delta_time);
    void change_rate_limit(double rate_limit_hz);
    void change_earliness_leniency(double earliness_leniency_seconds);

    double get_last_processed_time() const;

  private:
    double last_processed_time = 0.0;

    std::chrono::duration<double> rate_limit_duration;
    std::chrono::duration<double> earliness_leniency_duration;
    // AUTOMATIC TIME PROCESSING START
    std::chrono::steady_clock::time_point last_cycle_time;
    // AUTOMATIC TIME PROCESSING END
    // MANUAL TIME PROCESSING START
    double manual_time_processed_since_last_tick = 0.0;
    // MANUAL TIME PROCESSING END

    bool ran_during_cycle = false;
};
#endif // RATELIMITER_HPP
