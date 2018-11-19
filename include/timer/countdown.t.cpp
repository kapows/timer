#include "countdown.h"

#include "common.t.h"

#include <catch.hpp>

using countdown = timer::countdown<monotonic_clock>;
using namespace std::literals::chrono_literals;

TEST_CASE("observers")
{
  SECTION("default construct")
  {
    countdown x;
    REQUIRE(x.is_live() == false);
    REQUIRE((bool)x == x.is_live());
  }
  SECTION("duration construct")
  {
    countdown x(3s);
    REQUIRE(x.is_live() == true);
    REQUIRE((bool)x == x.is_live());
    REQUIRE(x.time_left() == 3s);
    monotonic_clock::advance(2s);
    REQUIRE(x.is_live() == true);
    REQUIRE((bool)x == x.is_live());
    REQUIRE(x.time_left() == 1s);
    monotonic_clock::advance(1s);
    REQUIRE(x.is_live() == false);
    REQUIRE((bool)x == x.is_live());
  }
}
TEST_CASE("modifiers")
{
  countdown x(3s);
  x += 1s;
  REQUIRE(x.is_live() == true);
  REQUIRE(x.time_left() == 4s);
  x -= 1s;
  REQUIRE(x.is_live() == true);
  REQUIRE(x.time_left() == 3s);
  x -= 3s;
  REQUIRE(x.is_live() == false);
}