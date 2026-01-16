#include "TimerManager.h"

mutex_t g_mtx;


TimerManager::TimerManager() : current_time_ms_(time_us_64() / 1000)
{
    mutex_init(&g_mtx);
}

TimerManager::~TimerManager()
{
    timers_.clear();
}

void TimerManager::CreateTimer(int repeat_ms, bool brepeat, std::function<void()> callback)
{
    mutex_enter_blocking(&g_mtx);
    timers_.push_back(std::make_unique<Timer>(repeat_ms, current_time_ms_, brepeat, callback));
    mutex_exit(&g_mtx);
}

void TimerManager::RemoveTimer(int index)
{   
    mutex_enter_blocking(&g_mtx);
    if(index < 0 || index >= timers_.size()){
        return;
    }
    timers_.erase(timers_.begin() + index);
    mutex_exit(&g_mtx);
}

void TimerManager::Tick()
{
    while (true)
    {
        mutex_enter_blocking(&g_mtx);

        current_time_ms_ = time_us_64() / 1000;

        if (timers_.empty()) {
            // release before sleeping!
            mutex_exit(&g_mtx);
            sleep_ms(1000);
            continue;
        }

        // check each timer
        for (size_t i = 0; i < timers_.size(); /* no increment here */)
        {
            auto &t = timers_[i];
            uint64_t due = t->GetCurrentMS() + t->GetRepeatMS();
            if (!t->GetbRepeat()) {
                if (current_time_ms_ > due) {
                    t->Recall();
                    // remove one‐shot
                    timers_.erase(timers_.begin() + i);
                    continue; // skip i++ so we re‐index correctly
                }
            } else {
                if (current_time_ms_ > due) {
                    t->Recall();
                    t->SetCurrentMS(current_time_ms_);
                }
            }
            ++i;
        }

        mutex_exit(&g_mtx);
        sleep_ms(10);
    }
}

TimerManager g_timerManager;
