#pragma once

#include <cassert> // assert
#include <chrono> // duration_cast

namespace timer
{
  template<typename Clock, typename Duration = typename Clock::duration>
  class countdown
  {
  private: // variables
    typename Clock::time_point end{Clock::now()};

  public: // constructors
    countdown(Duration const & duration = {}) noexcept : end{Clock::now() + duration}
    {
    }

  public: // observers
    bool is_live() const noexcept
    {
      return Clock::now() < end;
    }
    operator bool() const noexcept
    {
      return is_live();
    }
    auto time_left() const noexcept
    {
      assert(is_live());
      return std::chrono::duration_cast<Duration>(end - Clock::now());
    }

  public: // modifiers
    countdown & operator+=(Duration const & dt) noexcept
    {
      end += std::chrono::duration_cast<typename Clock::duration>(dt);
      return *this;
    }
    countdown & operator-=(Duration const & dt) noexcept
    {
      end -= std::chrono::duration_cast<typename Clock::duration>(dt);
      return *this;
    }
  };
}