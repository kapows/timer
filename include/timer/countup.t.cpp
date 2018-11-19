#include "countup.h"

#include "common.t.h"

#include <catch.hpp>

using countup = timer::countup<monotonic_clock>;
using namespace std::literals::chrono_literals;

TEST_CASE("observers")
{
  countup x;
  REQUIRE(x.time_elapsed() == 0s);
  monotonic_clock::advance(3s);
  REQUIRE(x.time_elapsed() == 3s);
}
TEST_CASE("modifiers")
{
  countup x;
  monotonic_clock::advance(5s);
  x -= 1s;
  REQUIRE(x.time_elapsed() == 4s);
  x += 1s;
  REQUIRE(x.time_elapsed() == 5s);
  REQUIRE(x.consume() == 5s);
  REQUIRE(x.consume() == 0s);
  monotonic_clock::advance(6s);
  REQUIRE(x.consume(3s) == true);
  REQUIRE(x.consume(3s) == true);
  REQUIRE(x.time_elapsed() == 0s);
  REQUIRE(x.consume(3s) == false);
}