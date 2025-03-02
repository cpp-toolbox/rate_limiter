#ifndef RATELIMITER_HPP
#define RATELIMITER_HPP

#include <chrono>

class RateLimiter {
  public:
    explicit RateLimiter(double rate_limit_hz);

    bool attempt_to_run();
    bool attempt_to_run(double delta_time);

    void change_rate_limit(double rate_limit_hz);

  private:
    std::chrono::duration<double> rate_limit_duration;
    // AUTOMATIC TIME PROCESSING START
    std::chrono::steady_clock::time_point last_run_time;
    // AUTOMATIC TIME PROCESSING END

    // MANUAL TIME PROCESSING START
    double manual_time_processed_since_last_tick = 0.0;
    // MANUAL TIME PROCESSING END
};

#endif // RATELIMITER_HPP
