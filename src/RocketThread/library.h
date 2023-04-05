#pragma once

#include "RocketThreadAPI.h"
#include <functional>

class ROCKETTHREAD_API RocketThread
{
public:
    RocketThread();

    /**
     * Run the task on a std::thread
     */
    bool ExecuteTask(std::function<void> task, std::function<void> taskCompleteCallback = nullptr);
    /**
     * Run the task on an Intel TBB thread with optional settings for priority and whether to force the use of performance cores
     */
    bool ExecuteTBBTask(std::function<void> task, std::function<void> taskCompleteCallback = nullptr, bool bForcePerformanceCore = false, bool bForceHighPriority = false);

};

