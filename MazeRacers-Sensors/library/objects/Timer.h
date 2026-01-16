#ifndef _TIMER_H_
#define _TIMER_H_

#include <iostream>
#include <functional>
#include <cstdint>

class Timer
{
public:
    Timer(int repeat_ms, int current_ms, bool brepeat, std::function<void()> callback);
    ~Timer();

    void Stop(); 
    void Recall();

    const void SetCurrentMS(uint64_t current_ms);

    bool GetbRepeat() const;
    int GetCount() const;
    uint64_t GetRepeatMS() const;
    uint64_t GetCurrentMS() const;
private:
    int count_;
    uint64_t repeat_ms_;
    uint64_t current_ms_;
    bool brepeat_;
    std::function<void()> callback_;
};

#endif