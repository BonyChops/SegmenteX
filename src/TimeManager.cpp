//
// Created by bonychops on 12/12/21.
//

#include <chrono>
#include "TimeManager.h"

TimeManager::TimeManager() {
    long currentTime = (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
    bufTime = currentTime;
}

TimeManager::~TimeManager() {}

int TimeManager::deltaTime() {
    long currentTime = (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
    long result = currentTime - (long)bufTime;
    bufTime = currentTime;
    return (int)result;
}