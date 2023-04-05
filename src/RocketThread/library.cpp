#include "library.h"
#include <thread>


RocketThread::RocketThread()
{

}

bool ExecuteTask(std::function<void> task, std::function<void> taskCompleteCallback = nullptr);
{
    std::thread taskThread([&]()
                           {
                               task();
                               if (taskCompleteCallback != nullptr)
                               {
                                   taskCompleteCallback();
                               }
                           });
    taskThread.join();
    return true;
}

bool ExecuteTBBTask(std::function<void> task, std::function<void> taskCompleteCallback = nullptr, bool bForcePerformanceCore = false, bool bForceHighPriority = false);
{
    // Use all performace cores? - Check with CPU stats how many there are
    tbb::global_control gc(tbb::global_control::max_allowed_parallelism, 4);

    // Create arena constraints based on the input parameters
    tbb::task_arena::constraints arenaConstraints;
    if (bForcePerformanceCore)
    {
        arenaConstraints.set_numa_binding_mode(tbb::task_arena::constraints::bind_to_core);
    }
    if (bForceHighPriority)
    {
        arenaConstraints.set_priority(tbb::task_arena::constraints::priority::high);
    }

    // Create an arena with the specified constraints
    tbb::task_arena arena(tbb::task_arena::create(arena_constraints, tbb:task_arena::attach()));

    // Can enqueue multiple tasks to the arena
    arena.enqueue([&]()
    {
        task();
        if (taskCompleteCallback != nullptr)
        {
            taskCompleteCallback();
        }
    });
}
