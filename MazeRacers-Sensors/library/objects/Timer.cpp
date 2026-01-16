#include "Timer.h"

#include <iostream>
#include <cstdint>

Timer::Timer(int repeat_ms, int current_ms, bool brepeat, std::function<void()> callback) : repeat_ms_(repeat_ms), current_ms_(current_ms), brepeat_(brepeat), count_(0), callback_(std::move(callback))
{
}

Timer::~Timer()
{
}

void Timer::Stop()
{
    brepeat_ = false;
}

uint64_t Timer::GetRepeatMS() const
{
    return repeat_ms_;
}

uint64_t Timer::GetCurrentMS() const
{
    return current_ms_;
}

bool Timer::GetbRepeat() const
{
    return brepeat_;
}

int Timer::GetCount() const
{
    return count_;
}

void Timer::Recall()
{
    if(callback_){
        callback_(); 
        count_++;
    }
}

const void Timer::SetCurrentMS(uint64_t current_ms)
{
    current_ms_ = current_ms;
}
