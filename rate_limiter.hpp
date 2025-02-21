#ifndef RATELIMITER_HPP
#define RATELIMITER_HPP

#include <chrono>

class RateLimiter {
  public:
    explicit RateLimiter(int rate_limit_hz);
    bool attempt_to_run();
    void change_rate_limit(int rate_limit_hz);

  private:
    std::chrono::milliseconds rate_limit_duration;
    std::chrono::steady_clock::time_point last_run_time;
};

#endif // RATELIMITER_HPP
