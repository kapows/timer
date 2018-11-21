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

So if you need to wait some time to fire off something once, you'll probably go with the count down timer.
If you want to work with delta time, you'll probably go with the count up timer and consume elapsed time as a whole.
If you want to work with a fixed time step, you'll probably go with the count up timer and consume elapsed time in chunks.
