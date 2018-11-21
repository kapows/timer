# timer

Easy to use timers for C++17.

## Design

There are two timers, one counts up, the other counts down.
We can used a fixed time point as state for both of theses timers as when time increases, the "state" of both kinds of timers change.
The difference between the internal time point of the count up timer and actual time gets larger. 
The difference between the internal time point of the count down timer gets smaller. 
Thus there is no need to continuously update the timers through some time step mechanism.
For any sort of fixed time step or variable time step we can leave that up to the "Clock" that the user has to pass to the timers.

These timers are not event based. They must be polled for their state. The count down timer is simple, it is either "live" or not. 
The count up timer is always "live", and the way to work with it is to either use its time elapsed, or
to consume the time that it has elapsed as a whole, or consume that time in chunks.

## Use

Do something after a set period of time.

```cpp
#include <timer.h>
#include <chrono>

using namespace std::literals::chrono_literals;
using namespace timer;

int main()
{
  countdown<std::chrono::steady_clock> t = {10s};
  while(t) {
    // spin for 10 seconds
  }
  // Do something after 10 seconds
  return 0;
}
```

Do something every x seconds.

```cpp
#include <timer.h>
#include <chrono>

using namespace std::literals::chrono_literals;
using namespace timer;

int main()
{
  countup<std::chrono::steady_clock> t;
  while(true) {
    if(t.consume(3s)) {
      cout << "Hello" << endl;
    }
  }
  return 0;
}
```

Update from last call.

```cpp
#include <timer.h>
#include <chrono>

using namespace std::literals::chrono_literals;
using namespace timer;

int main()
{
  timer::countup<std::chrono::steady_clock, std::chrono::duration<float>> t;
  float position = 0.0f;
  float velocity = 1.0f;

  while (position < 100.0f)
  {
    auto dt = t.consume();
    position = position + velocity * dt.count();
    std::cout << position << std::endl;
  }
  return 0;
}
```

## Install

### Shell

```Shell
git clone https://github.com/kapows/timer && cd timer
mkdir build && cd build
cmake .. -G Ninja -DCMAKE_INSTALL_PREFIX=$INSTALL_PATH
cmake --build . --target install --config Release
```

### Cmake

```Cmake
find_package(timer CONFIG REQUIRED)
target_link_libraries(main PRIVATE timer::timer)
```

## Develop

### Shell

```Shell
vcpkg install catch2
git clone https://github.com/kapows/timer && cd timer
mkdir build && cd build
cmake .. -G Ninja -DBUILD_TESTING=ON -DCMAKE_TOOLCHAIN_FILE=$VCPKG_PATH 
cmake --build . --config Debug
ctest
```