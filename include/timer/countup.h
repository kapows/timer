#pragma once

#include <chrono> // duration_cast
namespace timer
{
  template<typename Clock, typename Duration = typename Clock::duration>
  class countup
  {
  private: // variables
    typename Clock::time_point start{Clock::now()};

  public: // observers
    auto time_elapsed() const noexcept
    {
      return std::chrono::duration_cast<Duration>(Clock::now() - start);
    }

  public: // modifiers
    countup & operator+=(Duration const & dt) noexcept
    {
      start -= dt;
      return *this;
    }
    countup & operator-=(Duration const & dt) noexcept
    {
      start += dt;
      return *this;
    }
    auto consume() noexcept
    {
      auto x = time_elapsed();
      *this -= x;
      return x;
    }
    bool consume(Duration const & dt) noexcept
    {
      auto x = time_elapsed();
      if (dt <= x)
      {
        *this -= dt;
        return true;
      }
      return false;
    }
  };

}