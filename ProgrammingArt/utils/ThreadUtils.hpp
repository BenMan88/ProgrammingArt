#pragma once
#include <functional>

/** Spawns a new thread running function */
void spawnThread(const std::function<void()> &function);

/** 
 * Will pass toCall into inFunction, and wait until toCall has been completed.
 * before returning 
 * 
 * @param inFunction this should take a function and execute it's input some time later
 * @param toCall The function to call and wait for
 * */
void syncOnThread(std::function<void(const std::function<void()> &)> inFunction, const std::function<void()> &toCall);