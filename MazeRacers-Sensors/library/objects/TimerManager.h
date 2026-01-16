#ifndef TIMER_MANAGER_H_
#define TIMER_MANAGER_H_

#include <iostream>
#include <memory>
#include <vector>
#include <functional>

#include "pico/stdlib.h"
#include "pico/multicore.h"
#include "hardware/timer.h"

#include "Timer.h"

extern mutex_t g_mtx;

class TimerManager
{
public:
    TimerManager();
    ~TimerManager();
    void Tick();
    void CreateTimer(int repeat_ms, bool brepeat, std::function<void()> callback);
    void RemoveTimer(int index);
private:
    std::vector<std::unique_ptr<Timer>> timers_;
    uint64_t current_time_ms_;
};

extern TimerManager g_timerManager;

#endif