#include "ThreadUtils.hpp"
#include <thread>
#include <mutex>
#include <condition_variable>

void spawnThread(const std::function<void()> &function){
    std::thread thread(function);
    thread.detach();
}

void syncOnThread(std::function<void(const std::function<void()>&)> inFunction, const std::function<void()> &toCall) {
    std::mutex doneCallAfter;
    
    std::unique_lock<std::mutex> lockGuard(doneCallAfter);
    std::condition_variable isDoneCondition;
    
    bool isCalled = false;
    inFunction([&toCall, &doneCallAfter, &isDoneCondition, &isCalled](){
        toCall();
        std::unique_lock<std::mutex> lockGuard(doneCallAfter);

        isCalled = true;
        isDoneCondition.notify_all();

    });

    
    isDoneCondition.wait(lockGuard, [&isCalled]() -> bool {
       return isCalled; 
    });
}