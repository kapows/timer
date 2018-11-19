#pragma once

#include <chrono>

class monotonic_clock
{
public: // typedefs
  using rep = int;
  using period = std::ratio<1>;
  using duration = std::chrono::duration<rep, period>;
  using time_point = std::chrono::time_point<monotonic_clock>;
  static constexpr auto is_steady = true;

private: // variables
  inline static time_point my_now = {};

public:
  static auto now() noexcept
  {
    return my_now;
  }
  static void advance(duration const & x) noexcept
  {
    my_now += x;
  }
};